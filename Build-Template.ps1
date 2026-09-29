<#
.SYNOPSIS
    Packages the mini-filter driver project template into a ZIP file and optionally
    installs it into the Visual Studio 2026 user templates folder.

.PARAMETER Install
    Copies the created ZIP file into the user project templates folder.

.PARAMETER TemplatesDir
    Explicitly specifies the installation folder.
    Default: <Documents>\Visual Studio 18\Templates\ProjectTemplates

.EXAMPLE
    .\Build-Template.ps1 -Install
#>
[CmdletBinding()]
param(
    [switch]$Install,
    [string]$TemplatesDir
)

$ErrorActionPreference = 'Stop'

$sourceDir = Join-Path $PSScriptRoot 'Template'
$distDir   = Join-Path $PSScriptRoot 'dist'
$zipPath   = Join-Path $distDir 'FileSystemMiniFilter.zip'

New-Item -ItemType Directory -Force $distDir | Out-Null
if (Test-Path $zipPath) {
    Remove-Item $zipPath -Force
}

# Compress only the folder contents so that the .vstemplate is at the root of the ZIP
Compress-Archive -Path (Join-Path $sourceDir '*') -DestinationPath $zipPath
Write-Host "Created: $zipPath"

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
