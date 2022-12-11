
# foo_preview

[foo_preview](https://github.com/stuerp/foo_preview/releases) is a [foobar2000](https://www.foobar2000.org/) component that adds a **Preview** playback mode.

## Features

* Supports foobar2000 2.0 (32-bit and 64-bit version)
* Supports dark mode.

## Requirements

* Microsoft Windows 10 or later
* [foobar2000](https://www.foobar2000.org/download) v2.0 or later

## Getting started

* Double-click `foo_preview.fbk2-component`.

or

* Import `foo_preview.fbk2-component` into foobar2000 using "File / Preferences / Components / Install...".

Configure the component using Preferences:

* Start time type
    * In seconds
    * As percentage of track length
    * Random
* Preview length in seconds

## Developing

The code builds out-of-the box with Visual Studio.

### Requirements

To build the code:

* [Microsoft Visual Studio 2022 Community Edition](https://visualstudio.microsoft.com/downloads/) or later.
* [foobar2000 SDK](https://www.foobar2000.org/SDK) 2022-20-20.
* [Windows Template Library (WTL)](https://github.com/Win32-WTL/WTL) 10.0.10320.

To create the deployment package:

* [PowerShell 7.2](https://github.com/PowerShell/PowerShell) or later.

### Setup

Create the following directory structure:

    3rdParty
        WTL10_10320
    bin
        x86
    foo_preview
    out
    sdk

* `3rdParty/WTL10_10320` contains WTL 10.0.10320.
* `bin` contains a portable version of foobar2000 2.0 for debugging purposes.
* `bin/x86` contains a portable version of foobar2000 1.6 for debugging purposes.
* `foo_preview` contains the [Git](https://github.com/stuerp/foo_preview) repository.
* `out` receives a deployable version of the component.
* `sdk` contains the foobar2000 SDK.

### Building

Open `foo_preview.sln` with Visual Studio and build the solution.

## Contributing

If you'd like to contribute, please fork the repository and use a feature
branch. Pull requests are warmly welcome.

## Change Log

### v1.0.0, 2022-11-01, *"Scratchin' the itch"*

* Initial release

## Build

* Builds with Microsoft Visual Studio Community 2022.

## Reference

* [foobar2000 Development](https://wiki.hydrogenaud.io/index.php?title=Foobar2000:Development:Overview)

## Acknowledgements / Credits

* Peter Pawlowski, for the [foobar2000](https://www.foobar2000.org/) audio player. ![foobar2000](https://www.foobar2000.org/button-small.png).
* Based on ideas from [foo_preview](https://www.foobar2000.org/components/view/foo_preview) by grimes.

## Reference Material

* [Desktop app user interface](https://learn.microsoft.com/en-us/windows/win32/windows-application-ui-development)
* [Windows User Experience Interaction Guidelines](https://learn.microsoft.com/en-us/windows/win32/uxguide/guidelines)
* [Windows Controls](https://learn.microsoft.com/en-us/windows/win32/controls/window-controls)
* [Control Library](https://learn.microsoft.com/en-us/windows/win32/controls/individual-control-info)
* [Resource-Definition Statements](https://learn.microsoft.com/en-us/windows/win32/menurc/resource-definition-statements)
* [Visuals, Layout](https://learn.microsoft.com/en-us/windows/win32/uxguide/vis-layout)

## Links

* Home page: https://github.com/stuerp/foo_preview
* Repository: https://github.com/stuerp/foo_preview.git
* Issue tracker: https://github.com/stuerp/foo_preview/issues

## License

![License: MIT](https://img.shields.io/badge/license-MIT-yellow.svg)
