# NEXUS MOD MENU

A modern-premium Geometry Dash utility mod built with the Geode SDK.

## Design
- Graphite / near-black visual direction
- Electric-blue primary accent and subtle violet secondary accent
- Compact, touch-friendly menu concept
- Original NEXUS identity (not a copy of Mega Hack branding)

## Current implementation
- Geode mod project scaffold
- Main-menu entry point
- Initial NEXUS welcome panel
- GitHub Actions builds for Android ARM64 and Windows x64

## Build artifacts
Open **Actions**, select the latest successful **Build NEXUS Geode Mod** run, and download:
- `nexus-android64`
- `nexus-win64`

Each artifact contains a `.geode` package, not an APK.

## Compatibility
The project currently targets Geometry Dash 2.2081 and Geode SDK 5.11.2 or newer. Actual compatibility depends on the installed game and Geode versions.

## Roadmap
The first commit establishes a buildable foundation. Player, Level, Editor, Visuals, and Misc controls must be implemented and tested individually before being described as working. No placeholder switch is presented as a functional feature.

## Install
Copy the platform-matching `.geode` package into your Geode mods folder, then launch Geometry Dash and enable the mod in Geode if needed.
