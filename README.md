# Filter Driver: Filesystem Mini-filter Template (Visual Studio 2026)

A replacement for the "Filter Driver: Filesystem Mini-filter" project template that was removed from the WDK starting with Visual Studio 2019.
([Background - Microsoft Q&A](https://learn.microsoft.com/en-us/answers/questions/1428782/why-the-template-filter-driver-filesystem-mini-fil))

It is based on the structure of the official Microsoft sample [passThrough](https://github.com/microsoft/Windows-driver-samples/tree/main/filesys/miniFilter/passThrough) and builds as-is with the current WDK.

## Requirements

- Visual Studio 2026 ("Desktop development with C++" workload)
- Windows Driver Kit (WDK) and the WDK extension for Visual Studio

## Build

```powershell
.\Build-Template.ps1
```

This creates the following files in `dist\`:

| File | Description |
|---|---|
| `FileSystemMiniFilter.vsix` | Visual Studio extension that contains the project template |
| `FileSystemMiniFilter.zip` | Project template ZIP for the user templates folder |

## Installation

Use either the VSIX or the ZIP, not both. If both are installed, the template appears twice in "Create a new project".

### VSIX (recommended)

Double-click `dist\FileSystemMiniFilter.vsix`, or run:

```powershell
& "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\VSIXInstaller.exe" dist\FileSystemMiniFilter.vsix
```

The extension is installed per user and does not require administrator rights.
To uninstall, open Extensions > Manage Extensions in Visual Studio, or run:

```powershell
& "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\VSIXInstaller.exe" /uninstall:FileSystemMiniFilterTemplate.7c3f1b52-4e0a-4d8b-9a61-2f5e8d0c9b17
```

To release a new version, increase `Version` in [Vsix/extension.vsixmanifest](Vsix/extension.vsixmanifest) and rebuild.

### ZIP

```powershell
.\Build-Template.ps1 -Install
```

This copies `dist\FileSystemMiniFilter.zip` to `<Documents>\Visual Studio 18\Templates\ProjectTemplates`.
The correct location is used even if the Documents folder is redirected to OneDrive.
If you have changed the user templates location in Visual Studio (Tools > Options > Projects and Solutions > Locations), specify it with `-TemplatesDir`.

If Windows Security "Controlled folder access" is enabled, the copy from PowerShell is blocked and fails with a "Could not find file" error. In that case, copy the ZIP with File Explorer or use the VSIX instead.

To uninstall, delete the copied ZIP file.

### Using the template

Restart Visual Studio and search for "**Filter Driver: Filesystem Mini-filter**" in "Create a new project" (you can filter by Language: C++, Platform: Windows, and Project type: Driver).

## Generated project

| File | Description |
|---|---|
| `<name>.cpp` | C++ source. DriverEntry, Unload, instance management callbacks, and pre/post-operation callbacks. Only IRP_MJ_CREATE is enabled; the other IRP_MJ entries are provided in an `#if 0` block |
| `<name>.inf` | INF for installing the mini-filter. On Windows build 25952 and later the driver runs from the driver store; on earlier builds it runs from `system32\drivers` |
| `<name>.rc` | Version resource |

Main project settings:

- Platforms: x64 / ARM64 (Debug / Release)
- Toolset: `WindowsKernelModeDriver10.0`, driver type: WDM, target platform: Universal
- Links `fltMgr.lib`
- Warning level 4, warnings treated as errors
- `/utf-8` (source files are compiled as UTF-8)
