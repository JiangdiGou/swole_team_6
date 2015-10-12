# You can place the script of your game in this file.

# Declare images below this line, using the image statement.
# eg. image eileen happy = "eileen_happy.png"

# Declare characters used by this game.


# The game starts here.
label start:
    menu:
        "Existing file or new file?"
        "Existing":
            jump existing
        "New":
            jump new

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
    hide screen say
    show screen gui_menu(levelStruct)
    jump loop1

label loop1:
    ""
    show screen gui_menu(levelStruct)
    jump loop1