<#
.SYNOPSIS
    Expands the template the same way Visual Studio does (parameter replacement)
    and builds all configurations with MSBuild to verify it.

.PARAMETER ProjectName
    Name of the project to generate. Names containing spaces are allowed
    (they are replaced with "_" in $safeprojectname$).

.PARAMETER OutputDir
    Folder to expand the project into. Default: .\test-output\<timestamp>
    (The temp folder is avoided because MSBuild reports warning MSB8029 there.)

.PARAMETER Configurations
    Configurations to build.

.PARAMETER Platforms
    Platforms to build.

.EXAMPLE
    .\Test-Template.ps1 -ProjectName "My Filter" -Platforms x64
#>
[CmdletBinding()]
param(
    [string]$ProjectName = 'TestMiniFilter',
    [string]$OutputDir = (Join-Path $PSScriptRoot "test-output\$(Get-Date -Format 'yyyyMMdd-HHmmss')"),
    [string[]]$Configurations = @('Debug', 'Release'),
    [string[]]$Platforms = @('x64', 'ARM64')
)

$ErrorActionPreference = 'Stop'

$sourceDir    = Join-Path $PSScriptRoot 'Template'
$templatePath = Join-Path $sourceDir 'MiniFilter.vstemplate'

# Like Visual Studio's $safeprojectname$, replace characters not valid in identifiers with "_"
$safeName = $ProjectName -replace '[^A-Za-z0-9_]', '_'
if ($safeName -match '^[0-9]') {
    $safeName = "_$safeName"
}

$parameters = [ordered]@{
    '$projectname$'     = $ProjectName
    '$safeprojectname$' = $safeName
    '$guid1$'           = [Guid]::NewGuid().ToString('D').ToUpperInvariant()
    '$year$'            = (Get-Date).Year.ToString()
}

function Expand-TemplateText([string]$text) {
    foreach ($key in $parameters.Keys) {
        $text = $text.Replace($key, $parameters[$key])
    }
    return $text
}

function Copy-TemplateFile([string]$source, [string]$targetName, [bool]$replace) {
    $sourcePath = Join-Path $sourceDir $source
    $targetPath = Join-Path $projectDir (Expand-TemplateText $targetName)

    if (-not $replace) {
        Copy-Item $sourcePath $targetPath
        return
    }

    # Preserve whether the file has a BOM
    $bytes  = [IO.File]::ReadAllBytes($sourcePath)
    $hasBom = $bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF
    $text   = [IO.File]::ReadAllText($sourcePath, [Text.Encoding]::UTF8)
    [IO.File]::WriteAllText($targetPath, (Expand-TemplateText $text), (New-Object Text.UTF8Encoding $hasBom))
}

#
# Expand the template
#

[xml]$template = Get-Content $templatePath -Raw
$ns = New-Object Xml.XmlNamespaceManager $template.NameTable
$ns.AddNamespace('t', 'http://schemas.microsoft.com/developer/vstemplate/2005')

$projectDir = Join-Path $OutputDir $ProjectName
New-Item -ItemType Directory -Force $projectDir | Out-Null

$projectNode = $template.SelectSingleNode('//t:TemplateContent/t:Project', $ns)
Copy-TemplateFile $projectNode.File $projectNode.TargetFileName ($projectNode.ReplaceParameters -eq 'true')
$projectFile = Join-Path $projectDir (Expand-TemplateText $projectNode.TargetFileName)

foreach ($item in $projectNode.SelectNodes('t:ProjectItem', $ns)) {
    Copy-TemplateFile $item.InnerText $item.TargetFileName ($item.ReplaceParameters -eq 'true')
}

# Detect unreplaced parameters ($ARCH$ in the INF is handled by StampInf at build time)
$leftovers = Get-ChildItem $projectDir -File |
    Select-String -Pattern '\$[A-Za-z0-9_]+\$' -AllMatches |
    ForEach-Object { $_.Matches.Value } |
    Where-Object { $_ -ne '$ARCH$' } |
    Sort-Object -Unique
if ($leftovers) {
    throw "Unreplaced template parameters found: $($leftovers -join ', ')"
}

Write-Host "Expanded: $projectDir"

#
# Build
#

$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$msbuild = & $vswhere -latest -prerelease -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\amd64\MSBuild.exe' | Select-Object -First 1
if (-not $msbuild) {
    throw 'MSBuild was not found.'
}

$results = foreach ($platform in $Platforms) {
    foreach ($configuration in $Configurations) {
        Write-Host "`n=== $configuration|$platform ==="
        & $msbuild $projectFile /nologo /v:minimal /restore:false "/p:Configuration=$configuration" "/p:Platform=$platform" | Out-Host
        [pscustomobject]@{
            Configuration = $configuration
            Platform      = $platform
            Result        = if ($LASTEXITCODE -eq 0) { 'OK' } else { "FAILED ($LASTEXITCODE)" }
        }
    }
}

$results | Format-Table -AutoSize

if ($results | Where-Object Result -ne 'OK') {
    exit 1
}
