label start:
    $ renpy.reset_physical_size()
    if(persistent.scripts == "" or persistent.scripts is None):
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
    if(persistent.scripts == "" or persistent.scripts is None):
        jump folderWarning
    return

label folderWarning:
    "Returning to Main Menu. You must have a valid folder selected."
    return

label fileWarning:
    "Returning to Main Menu. You must have a valid file selected."
    return

label existing:
    $ state = scriptsToRegistrar(persistent.scripts)
    if (not state):
        "Illegal operation attempted. Scripts folder is likely not the Swole Team 6 folder. Aborting."
        return
    $ loadLevel = ui_find_file("Select the Level file.", home)
    $ guiView = View()
    "Loading [loadLevel]...{nw}"
    $ levelStruct = Level()
    $ levelStruct.loadFrom(loadLevel)
    if(not levelStruct.UsableState):
        jump fileWarning
    show screen gui_menu(levelStruct, guiView)
    jump loop1

label new:
    $ state = scriptsToRegistrar(persistent.scripts)
    if (not state):
        "Illegal operation attempted. Scripts folder is likely not the Swole Team 6 folder. Aborting."
        return
    $ guiView = View()
    $ levelStruct = Level()
    $ levelStruct.LevelName = renpy.input("Name of level:")
    $ levelStruct.ArrayWidth = renpy.input("Width of level:")
    $ levelStruct.ArrayHeight = renpy.input("Height of level:")
    $ levelStruct.FileLoc =  ui_find_folder("Select where to save the Level file.", home)
    if(levelStruct.FileLoc == "" or levelStruct.FileLoc is None):
        jump folderWarning
    $ baselineFile = renpy.input("Name the file")
    $ levelStruct.FileLoc += ("/" + baselineFile)
    $ levelStruct.initFile()
    if(not levelStruct.UsableState):
        jump fileWarning
    show screen gui_menu(levelStruct, guiView)
    jump loop1

label quickDebugNew:
    $ state = scriptsToRegistrar(persistent.scripts)
    if (not state):
        "Illegal operation attempted. Scripts folder is likely not the Swole Team 6 folder. Aborting."
        return
    $ guiView = View()
    $ levelStruct = Level()
    $ levelStruct.LevelName = "Debug Level"
    $ levelStruct.ArrayWidth = "45"
    $ levelStruct.ArrayHeight = "14"
    $ levelStruct.FileLoc =  ui_find_folder("Select where to save the Level file.", home)
    if(levelStruct.FileLoc == "" or levelStruct.FileLoc is None):
        jump folderWarning
    $ baselineFile = "ProjectTest.txt"
    $ levelStruct.FileLoc += ("/" + baselineFile)
    $ levelStruct.initFile()
    show screen gui_menu(levelStruct, guiView)
    jump loop1

label loop1:
    show screen gui_menu(levelStruct, guiView)
    hide screen disableGui
    hide screen understood
    ""
    jump loop1

label modPreset(newSet):
    $ guiView.preset = newSet
    jump loop1

label newName:
    show screen disableGui
    $ temp = renpy.input("New name of level:")
    $ levelStruct.saveState()
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
        jump loop1
    $ levelStruct.saveState()
    $ levelStruct.tileChange(guiView.x, guiView.y, temp)
    $ levelStruct.writeFile()
    jump loop1

label doUndo:
    if(levelStruct.UndoState == None):
        hide screen disableGui
        show screen understood
        "Nothing to undo."
        jump loop1
    $ levelStruct = levelStruct.UndoState
    $ levelStruct.writeFile()
    jump loop1

label insLeft:
    if(guiView.x == -1 or guiView.y == -1):
        "Bad tile."
        jump loop1
    $ levelStruct.saveState()
    $ levelStruct.insert("left", guiView.x)
    $ levelStruct.writeFile()
    jump loop1

label insRight:
    if(guiView.x == -1 or guiView.y == -1):
        "Bad tile."
        jump loop1
    $ levelStruct.saveState()
    $ levelStruct.insert("right", guiView.x)
    $ levelStruct.writeFile()
    jump loop1

label insUp:
    if(guiView.x == -1 or guiView.y == -1):
        "Bad tile."
        jump loop1
    $ levelStruct.saveState()
    $ levelStruct.insert("up", guiView.y)
    $ levelStruct.writeFile()
    jump loop1

label insDown:
    if(guiView.x == -1 or guiView.y == -1):
        "Bad tile."
        jump loop1
    $ levelStruct.saveState()
    $ levelStruct.insert("down", guiView.y)
    $ levelStruct.writeFile()
    jump loop1

