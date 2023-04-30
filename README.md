
# foo_previewer

[foo_previewer](https://github.com/stuerp/foo_previewer/releases) is a [foobar2000](https://www.foobar2000.org/) component that adds a **Preview** playback mode.

## Features

* Supports dark mode.

## Requirements

* Tested on Microsoft Windows 10 and later.
* [foobar2000](https://www.foobar2000.org/download) v1.6.16 or later (32 or 64-bit). ![foobar2000](https://www.foobar2000.org/button-small.png)

## Getting started

* Double-click `foo_previewer.fbk2-component`.

or

* Import `foo_previewer.fbk2-component` into foobar2000 using "File / Preferences / Components / Install...".

Configure the component using Preferences:

* Start time type
    * In seconds
    * As percentage of track length
    * Random
* Preview length in seconds

## Developing

The code builds out-of-the box with Visual Studio 2022.

### Requirements

To build the code you need:

* [Microsoft Visual Studio 2022 Community Edition](https://visualstudio.microsoft.com/downloads/) or later
* [foobar2000 SDK](https://www.foobar2000.org/SDK) 2023-04-18
* [Windows Template Library (WTL)](https://github.com/Win32-WTL/WTL) 10.0.10320

To create the deployment package:

* [PowerShell 7.2](https://github.com/PowerShell/PowerShell) or later

### Setup

Create the following directory structure:

    3rdParty
        WTL10_10320
    bin
        x86
    foo_previewer
    out
    sdk

* `3rdParty/WTL10_10320` contains WTL 10.0.10320.
* `bin` contains a portable version of foobar2000 64-bit for debugging purposes.
* `bin/x86` contains a portable version of foobar2000 32-bit for debugging purposes.
* `foo_previewer` contains the [Git](https://github.com/stuerp/foo_previewer) repository.
* `out` receives a deployable version of the component.
* `sdk` contains the foobar2000 SDK.

### Building

Open `foo_previewer.sln` with Visual Studio and build the solution.

### Packaging

To create the component first build the x86 configuration and next the x64 configuration.

## Contributing

If you'd like to contribute, please fork the repository and use a feature
branch. Pull requests are warmly welcome.

## Change Log

### v1.0.1, 2023-04-30, *"There can be only one"*

* Renamed the component to avoid being confused with [foo_preview](https://www.foobar2000.org/components/view/foo_preview) by grimes. Please manually uninstall the previous foo_preview component before installing this version to avoid having duplicated 'Preview' commands.
* Recompiled with [foobar2000 SDK](https://www.foobar2000.org/SDK) 2023-04-18.

### v1.0.0, 2022-11-01, *"Scratchin' the itch"*

* Initial release

## Acknowledgements / Credits

* Peter Pawlowski, for the [foobar2000](https://www.foobar2000.org/) audio player. ![foobar2000](https://www.foobar2000.org/button-small.png).
* Based on ideas from [foo_preview](https://www.foobar2000.org/components/view/foo_preview) by grimes.

## Reference Material

### foobar2000

* [foobar2000 Development](https://wiki.hydrogenaud.io/index.php?title=Foobar2000:Development:Overview)

### Windows

* [Desktop app user interface](https://learn.microsoft.com/en-us/windows/win32/windows-application-ui-development)
* [Windows User Experience Interaction Guidelines](https://learn.microsoft.com/en-us/windows/win32/uxguide/guidelines)
* [Windows Controls](https://learn.microsoft.com/en-us/windows/win32/controls/window-controls)
* [Control Library](https://learn.microsoft.com/en-us/windows/win32/controls/individual-control-info)
* [Resource-Definition Statements](https://learn.microsoft.com/en-us/windows/win32/menurc/resource-definition-statements)
* [Visuals, Layout](https://learn.microsoft.com/en-us/windows/win32/uxguide/vis-layout)

## Links

* Home page: https://github.com/stuerp/foo_previewer
* Repository: https://github.com/stuerp/foo_previewer.git
* Issue tracker: https://github.com/stuerp/foo_previewer/issues

## License

![License: MIT](https://img.shields.io/badge/license-MIT-yellow.svg)
