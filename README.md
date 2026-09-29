# Filter Driver: Filesystem Mini-filter Template (Visual Studio 2026)

A replacement for the "Filter Driver: Filesystem Mini-filter" project template that was removed from the WDK starting with Visual Studio 2019.
([Background - Microsoft Q&A](https://learn.microsoft.com/en-us/answers/questions/1428782/why-the-template-filter-driver-filesystem-mini-fil))

It is based on the structure of the official Microsoft sample [passThrough](https://github.com/microsoft/Windows-driver-samples/tree/main/filesys/miniFilter/passThrough) and builds as-is with the current WDK.

## Requirements

- Visual Studio 2026 ("Desktop development with C++" workload)
- Windows Driver Kit (WDK) and the WDK extension for Visual Studio

## Installation

```powershell
.\Build-Template.ps1 -Install
```

This creates `dist\FileSystemMiniFilter.zip` and copies it to `<Documents>\Visual Studio 18\Templates\ProjectTemplates`.
The correct location is used even if the Documents folder is redirected to OneDrive.
If you have changed the user templates location in Visual Studio (Tools > Options > Projects and Solutions > Locations), specify it with `-TemplatesDir`.

Restart Visual Studio and search for "**Filter Driver: Filesystem Mini-filter**" in "Create a new project" (you can filter by Language: C++ and Project type: Driver).

To uninstall, delete the copied ZIP file.

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
