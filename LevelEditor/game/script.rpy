﻿label start:
    if(persistent.scripts == ""):
        "Returning to Main Menu. You must have a valid Scripts folder selected."
        return
    menu:
        "Existing file or new file?"
        "Existing":
            jump existing
        "New":
            jump new
        "QUICK":
            jump quickDebugNew

label modFolder:
    $ persistent.scripts = ui_find_folder("Select the Scripts folder", home)
    return

label existing:
    $ loadLevel = ui_find_file("Select the Level file.", home)
    $ guiView = View()
    "Loading [loadLevel]...{nw}"
    $ levelStruct = Level()
    $ levelStruct.loadFrom(loadLevel)
    show screen gui_menu(levelStruct, guiView)
    jump loop1

label new:
    $ scriptsToRegistrar(persistent.scripts)
    $ guiView = View()
    $ levelStruct = Level()
    $ levelStruct.LevelName = renpy.input("Name of level:")
    $ levelStruct.ArrayWidth = renpy.input("Width of level:")
    $ levelStruct.ArrayHeight = renpy.input("Height of level:")
    $ levelStruct.FileLoc =  ui_find_folder("Select where to save the Level file.", home)
    $ baselineFile = renpy.input("Name the file")
    $ levelStruct.FileLoc += ("/" + baselineFile)
    $ levelStruct.initFile()
    show screen gui_menu(levelStruct, guiView)
    jump loop1

label quickDebugNew:
    $ scriptsToRegistrar(persistent.scripts)
    $ guiView = View()
    $ levelStruct = Level()
    $ levelStruct.LevelName = "Debug Level"
    $ levelStruct.ArrayWidth = "45"
    $ levelStruct.ArrayHeight = "14"
    $ levelStruct.FileLoc =  ui_find_folder("Select where to save the Level file.", home)
    $ baselineFile = "ProjectTest.txt"
    $ levelStruct.FileLoc += ("/" + baselineFile)
    $ levelStruct.initFile()
    show screen gui_menu(levelStruct, guiView)
    jump loop1

label loop1:
    hide screen disableGui
    hide screen understood
    ""
    show screen gui_menu(levelStruct, guiView)
    jump loop1

label newName:
    show screen disableGui
    $ temp = renpy.input("New name of level:")
    $ levelStruct.LevelName = temp
    $ levelStruct.writeFile()
    jump loop1

label changeTile:
    #show screen disableGui
    #$ temp = renpy.input("New character:")
    $ temp = askTile(luaTiles)
    if temp not in luaChars:
        hide screen disableGui
        show screen understood
        "Bad chararcter."
        return
    $ levelStruct.tileChange(guiView.x, guiView.y, temp)
    $ levelStruct.writeFile()
    jump loop1