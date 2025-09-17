# JSON Configuration Conversion

This document describes the conversion from the original CFG configuration format to a more human-readable JSON format.

## Overview

The Diablo 2 maphack now supports JSON configuration files alongside the original CFG format. The JSON format is much more intuitive for humans to edit while maintaining full compatibility with the existing codebase.

## Configuration Loading Priority

1. **JSON First**: The system tries to load `d2hackmap.json` first
2. **CFG Fallback**: If JSON doesn't exist, it falls back to the original `d2hackmap.cfg`
3. **Backwards Compatible**: Existing CFG files continue to work without changes

## Key Improvements

### Human-Readable Values

**Before (CFG):**
```
Monster Resists Toggle: 1
Item Value Toggle: 1
Boss Monster Colour: 0xd3
Auto Invite Toggle: 1,VK_F9
```

**After (JSON):**
```json
{
  "display": {
    "monsterResists": true,
    "itemValue": true
  },
  "monsters": {
    "bossMonsterColor": "orange"
  },
  "hotkeys": {
    "autoInviteToggle": {
      "enabled": true,
      "key": "F9"
    }
  }
}
```

### Named Colors

Instead of hex values like `0x62`, you can now use:
- Named colors: `"red"`, `"blue"`, `"orange"`, `"purple"`, etc.
- Hex colors: `"#FF0000"` (red)
- Special values: `"auto"`, `"auto_hide"`

### Descriptive Keys

Instead of virtual key codes like `VK_F9`, you can now use:
- Function keys: `"F9"`, `"F11"`
- Numpad keys: `"Numpad1"`, `"NumpadMinus"`
- Special keys: `"Backspace"`, `"Insert"`, `"Slash"`

### Organized Structure

Settings are grouped logically:
- `general`: Basic configuration
- `hotkeys`: All keyboard shortcuts
- `display`: Visual settings and overlays
- `automap`: Map-related settings
- `visuals`: Graphics and effects
- `monsters`: Monster display settings
- `items`: Item-related settings
- `advanced`: Advanced features

### Descriptive Values

Instead of cryptic numbers, you can use descriptive strings:
- `"disabled"` / `"enabled"` instead of `0` / `1`
- `"exit_game"` / `"town_portal"` for chicken actions
- `"dual_display"` for exp display modes
- `"switch_position"` for scroll modes

## File Locations

- **JSON Config**: `113map/d2hackmap.json`
- **Original CFG**: `113map/d2hackmap.cfg` (still supported)

## Example JSON Structure

```json
{
  "general": {
    "showCfgCheckInfo": true,
    "enableLanguageCheck": true
  },
  "hotkeys": {
    "reloadConfig": "L",
    "permShowItemsToggle": {
      "enabled": true,
      "key": "NumpadMinus"
    }
  },
  "display": {
    "monsterResists": true,
    "itemValue": true,
    "showPing": true
  },
  "automap": {
    "minimapSize": 6,
    "minimapToggle": true,
    "levelNameColor": "white"
  },
  "visuals": {
    "lifeBarColor": "dark_green",
    "permShowOrbs": true
  }
}
```

## Migration Guide

1. **Keep your existing CFG**: Your current `d2hackmap.cfg` will continue to work
2. **Try the JSON**: Copy the provided `d2hackmap.json` and customize it
3. **Switch gradually**: You can switch between formats by renaming files
4. **Backup first**: Always backup your working configuration

## Color Reference

Available named colors:
- `white`, `red`, `green`, `blue`, `yellow`
- `orange`, `purple`, `light_blue`, `light_gray`
- `dark_gray`, `brown`, `dark_green`, `gray`

## Key Reference

Common key names:
- Letters: `"A"` to `"Z"`
- Numbers: `"0"` to `"9"`
- Function keys: `"F1"` to `"F12"`
- Numpad: `"Numpad1"` to `"Numpad9"`, `"NumpadPlus"`, `"NumpadMinus"`
- Special: `"Backspace"`, `"Insert"`, `"Slash"`, `"Comma"`, `"Period"`