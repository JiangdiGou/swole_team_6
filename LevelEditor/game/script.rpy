label start:
    menu:
        "Existing file or new file?"
        "Existing":
            jump existing
        "New":
            jump new
        "QUICK":
            jump quickDebugNew

label existing:
    $ loadLevel = ui_find_file("Select the Level file.", home)  
    "Loading [loadLevel]...{nw}"
    $ levelStruct = Level()
    return

label new:
    $ levelStruct = Level()
    $ levelStruct.LevelName = renpy.input("Name of level:")
    $ levelStruct.ArrayWidth = renpy.input("Width of level:")
    $ levelStruct.ArrayHeight = renpy.input("Height of level:")
    $ levelStruct.FileLoc =  ui_find_folder("Select where to save the Level file.", home)
    $ baselineFile = renpy.input("Name the file")
    $ levelStruct.FileLoc += ("/" + baselineFile)
    $ levelStruct.writeFile()
    show screen gui_menu(levelStruct)
    jump loop1

label quickDebugNew:
    $ levelStruct = Level()
    $ levelStruct.LevelName = "Debug Level"
    $ levelStruct.ArrayWidth = "20"
    $ levelStruct.ArrayHeight = "7"
    $ levelStruct.FileLoc =  ui_find_folder("Select where to save the Level file.", home)
    $ baselineFile = "ProjectTest.txt"
    $ levelStruct.FileLoc += ("/" + baselineFile)
    $ levelStruct.writeFile()
    show screen gui_menu(levelStruct)
    jump loop1

label loop1:
    ""
    show screen gui_menu(levelStruct)
    jump loop1

label newName:
    $ levelStruct.LevelName = renpy.input("New name of level:")
    jump loop1