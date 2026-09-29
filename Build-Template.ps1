<#
.SYNOPSIS
    Packages the mini-filter driver project template as a ZIP file and a VSIX
    extension, and optionally installs the ZIP into the Visual Studio 2026 user
    templates folder.

.DESCRIPTION
    Outputs:
      dist\FileSystemMiniFilter.zip   Project template ZIP (for the user templates folder)
      dist\FileSystemMiniFilter.vsix  Visual Studio extension containing the template

.PARAMETER Version
    Overrides the VSIX version (e.g. 1.2.3). Only the packaged manifest is changed;
    Vsix\extension.vsixmanifest is not modified.
    Default: the Version in Vsix\extension.vsixmanifest

.PARAMETER Install
    Copies the created ZIP file into the user project templates folder.
    (To install the VSIX instead, double-click dist\FileSystemMiniFilter.vsix.)

.PARAMETER TemplatesDir
    Explicitly specifies the installation folder for -Install.
    Default: <Documents>\Visual Studio 18\Templates\ProjectTemplates

.EXAMPLE
    .\Build-Template.ps1 -Install

.EXAMPLE
    .\Build-Template.ps1 -Version 1.2.3
#>
[CmdletBinding()]
param(
    [string]$Version,
    [switch]$Install,
    [string]$TemplatesDir
)

$ErrorActionPreference = 'Stop'

# VSIX versions are two to four numeric parts
if ($Version -and $Version -notmatch '^\d+(\.\d+){1,3}$') {
    throw "Invalid version '$Version'. Use two to four numeric parts, e.g. 1.2.3."
}

Add-Type -AssemblyName System.IO.Compression

$sourceDir    = Join-Path $PSScriptRoot 'Template'
$vsixDir      = Join-Path $PSScriptRoot 'Vsix'
$distDir      = Join-Path $PSScriptRoot 'dist'
$zipPath      = Join-Path $distDir 'FileSystemMiniFilter.zip'
$vsixPath     = Join-Path $distDir 'FileSystemMiniFilter.vsix'
$templateName = 'FileSystemMiniFilter'

New-Item -ItemType Directory -Force $distDir | Out-Null

#
# Project template ZIP
#

if (Test-Path $zipPath) {
    Remove-Item $zipPath -Force
}

# Compress only the folder contents so that the .vstemplate is at the root of the ZIP
Compress-Archive -Path (Join-Path $sourceDir '*') -DestinationPath $zipPath
Write-Host "Created: $zipPath"

#
# VSIX
#

function New-VsixPackage {
    $utf8 = New-Object Text.UTF8Encoding $false

    # Package entries: ordered map of entry name (forward slashes) -> content bytes
    $entries = [ordered]@{}

    $manifestPath = Join-Path $vsixDir 'extension.vsixmanifest'
    [xml]$vsixManifest = Get-Content $manifestPath -Raw
    if ($Version) {
        $vsixManifest.PackageManifest.Metadata.Identity.Version = $Version
        $manifestStream = New-Object IO.MemoryStream
        $vsixManifest.Save($manifestStream)
        $entries['extension.vsixmanifest'] = $manifestStream.ToArray()
        $manifestStream.Dispose()
    }
    else {
        $entries['extension.vsixmanifest'] = [IO.File]::ReadAllBytes($manifestPath)
    }
    $entries['Icon.ico'] = [IO.File]::ReadAllBytes((Join-Path $sourceDir '__TemplateIcon.ico'))

    # The template is stored unzipped, as the VSSDK does for Visual Studio 2017 and later
    foreach ($file in Get-ChildItem $sourceDir -File) {
        $entries["ProjectTemplates/$templateName/$($file.Name)"] = [IO.File]::ReadAllBytes($file.FullName)
    }

    # Template manifest (.vstman), which Visual Studio uses to discover the template
    $vstemplatePath = Get-ChildItem $sourceDir -Filter *.vstemplate | Select-Object -First 1
    [xml]$vstemplate = Get-Content $vstemplatePath.FullName -Raw
    $templateData = $vstemplate.VSTemplate.TemplateData.OuterXml
    $vstman = @"
<?xml version="1.0" encoding="utf-8"?>
<VSTemplateManifest Version="1.0" xmlns="http://schemas.microsoft.com/developer/vstemplatemanifest/2015">
  <VSTemplateContainer TemplateType="$($vstemplate.VSTemplate.Type)">
    <RelativePathOnDisk>$templateName</RelativePathOnDisk>
    <TemplateFileName>$($vstemplatePath.Name)</TemplateFileName>
    <VSTemplateHeader>
      $templateData
    </VSTemplateHeader>
  </VSTemplateContainer>
</VSTemplateManifest>
"@
    $entries['ProjectTemplates/templateManifest0.noloc.vstman'] = $utf8.GetBytes($vstman)

    # Setup engine manifests (manifest.json / catalog.json) required by Visual Studio 2017 and later
    $identity     = $vsixManifest.PackageManifest.Metadata.Identity
    $id           = $identity.Id
    $version      = $identity.Version
    $displayName  = $vsixManifest.PackageManifest.Metadata.DisplayName
    $description  = $vsixManifest.PackageManifest.Metadata.Description.'#text'
    $dependencies = [ordered]@{}
    foreach ($prerequisite in $vsixManifest.PackageManifest.Prerequisites.Prerequisite) {
        $dependencies[$prerequisite.Id] = $prerequisite.Version
    }

    $sha256       = [Security.Cryptography.SHA256]::Create()
    $idHash       = [BitConverter]::ToString($sha256.ComputeHash($utf8.GetBytes($id))).Replace('-', '').ToLowerInvariant()
    $sha256.Dispose()
    $extensionDir = "[installdir]\Common7\IDE\Extensions\$($idHash.Substring(0, 8)).$($idHash.Substring(8, 3))"
    $installSize  = [long]($entries.Values | Measure-Object -Property Length -Sum).Sum

    $manifestJson = [ordered]@{
        id           = $id
        version      = $version
        type         = 'Vsix'
        vsixId       = $id
        extensionDir = $extensionDir
        files        = @($entries.Keys | ForEach-Object { [ordered]@{ fileName = "/$_"; sha256 = $null } })
        installSizes = [ordered]@{ targetDrive = $installSize }
        dependencies = $dependencies
    }

    $componentDependencies = [ordered]@{ $id = $version }
    foreach ($key in $dependencies.Keys) {
        $componentDependencies[$key] = $dependencies[$key]
    }

    $catalogJson = [ordered]@{
        manifestVersion = '1.1'
        info            = [ordered]@{ id = "$id,version=$version"; manifestType = 'Extension' }
        packages        = @(
            [ordered]@{
                id                               = "Component.$id"
                version                          = $version
                type                             = 'Component'
                extension                        = $true
                automaticallyAddedByExtensionPack = $false
                dependencies                     = $componentDependencies
                localizedResources               = @(
                    [ordered]@{ language = 'en-US'; title = $displayName; description = $description }
                )
            },
            [ordered]@{
                id           = $id
                version      = $version
                type         = 'Vsix'
                payloads     = @([ordered]@{ fileName = (Split-Path $vsixPath -Leaf); size = $installSize })
                vsixId       = $id
                extensionDir = $extensionDir
                installSizes = [ordered]@{ targetDrive = $installSize }
            }
        )
    }

    $entries['manifest.json'] = $utf8.GetBytes(($manifestJson | ConvertTo-Json -Depth 10 -Compress))
    $entries['catalog.json']  = $utf8.GetBytes(($catalogJson | ConvertTo-Json -Depth 10 -Compress))

    # OPC content types for every file extension in the package
    $extensions = $entries.Keys | ForEach-Object { [IO.Path]::GetExtension($_).TrimStart('.').ToLowerInvariant() } | Sort-Object -Unique
    $contentTypes = @{
        vsixmanifest = 'text/xml'
        vstemplate   = 'text/xml'
        vstman       = 'text/xml'
        vcxproj      = 'text/xml'
        filters      = 'text/xml'
        json         = 'application/json'
        ico          = 'image/x-icon'
    }
    $typeLines = foreach ($extension in $extensions) {
        $contentType = if ($contentTypes.ContainsKey($extension)) { $contentTypes[$extension] } else { 'application/octet-stream' }
        "  <Default Extension=`"$extension`" ContentType=`"$contentType`" />"
    }
    $contentTypesXml = @"
<?xml version="1.0" encoding="utf-8"?>
<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
$($typeLines -join "`r`n")
</Types>
"@

    if (Test-Path $vsixPath) {
        Remove-Item $vsixPath -Force
    }

    $stream  = [IO.File]::Open($vsixPath, [IO.FileMode]::CreateNew)
    $archive = New-Object IO.Compression.ZipArchive $stream, ([IO.Compression.ZipArchiveMode]::Create)
    try {
        $all = [ordered]@{ '[Content_Types].xml' = $utf8.GetBytes($contentTypesXml) }
        foreach ($key in $entries.Keys) {
            $all[$key] = $entries[$key]
        }

        foreach ($name in $all.Keys) {
            $entry = $archive.CreateEntry($name, [IO.Compression.CompressionLevel]::Optimal)
            $entryStream = $entry.Open()
            try {
                $entryStream.Write($all[$name], 0, $all[$name].Length)
            }
            finally {
                $entryStream.Dispose()
            }
        }
    }
    finally {
        $archive.Dispose()
        $stream.Dispose()
    }
}

New-VsixPackage
Write-Host "Created: $vsixPath"

#
# Install the ZIP into the user templates folder
#

if ($Install) {
    if (-not $TemplatesDir) {
        # Use the API because the Documents folder may be redirected (e.g. to OneDrive)
        $documents    = [Environment]::GetFolderPath('MyDocuments')
        $TemplatesDir = Join-Path $documents 'Visual Studio 18\Templates\ProjectTemplates'
    }

    New-Item -ItemType Directory -Force $TemplatesDir | Out-Null
    Copy-Item $zipPath $TemplatesDir -Force
    Write-Host "Installed: $(Join-Path $TemplatesDir (Split-Path $zipPath -Leaf))"
    Write-Host 'Restart Visual Studio to see the template in "Create a new project".'
}
