init -2 python:
    import os
    def registerClick(x, y):
        renpy.log(str(x) + "," + str(y))
        guiView.x = x
        guiView.y = y
        renpy.jump("loop1")


init python:
    class View:
        x = -1
        y = -1
        def __init__(self):
            return

    class Level:
        FileLoc = ""
        LevelName = ""
        ArrayWidth = 0
        ArrayHeight = 0
        TileMap = []

        def __init__(self):
            return

        def writeFile(self):
            file = open(self.FileLoc, 'w+')
            #levelName Block
            file.write("%s\n" % "[LevelName]")
            file.write("%s\n" % self.LevelName)
            #arraySpecs Block
            file.write("%s\n" % "[ArraySpecs]")
            file.write("%s\n" % self.ArrayWidth)
            file.write("%s\n" % self.ArrayHeight)
            #tileMap Block
            file.write("%s\n" % "[TileMap]")
            for x in range(0, self.height()):
                self.TileMap.append("0"*(int(self.ArrayWidth)))
            for line in self.TileMap:
                file.write("%s\n" % line)
            return
        def height(self):
            return int(self.ArrayHeight)
        def width(self):
            return int(self.ArrayWidth)

screen gui_menu(lo, vi):
    #leftside
    frame:
        xpos 0
        xsize 260
        vbox:
            xsize 260
            ysize 400
            $ tempWidth = lo.width()
            $ tempHeight = lo.height()
            text "Name:"
            textbutton "[lo.LevelName]" xalign 0.5 action Jump("newName")
            text "Width:"
            textbutton "[tempWidth]" xalign 0.5 action NullAction()
            text "Height:"
            textbutton "[tempHeight]" xalign 0.5 action NullAction()
        vbox:
            xsize 260
            ypos 400
            text "Tile Selection"
            text "[vi.x], [vi.y]"
    #always show this leftside preset
    frame:
        xpos 0
        xsize 260
        ypos (config.screen_height - 450)
        ysize 200
        vbox:
            xsize 260
            text "View Presets"
            hbox:
                textbutton "1" action NullAction()
    frame:#righside
        xpos 1660
        xsize 260
        vbox:
            xsize 200
            textbutton "???"
    window:
        xsize 1400
        ysize (config.screen_height - 250)
        ypos (config.screen_height - 250)
        #side "c r":
        frame:
            has viewport id "gm":
                mousewheel True
                draggable True
                yinitial 0
            vbox:
                null height 10
                hbox:
                    null width 42
                    for x in range(0, lo.width()):
                        vbox:
                            null width 42
                            text "[x]"  
                ysize (lo.height() * 42)
                for y in range(0, lo.height()):
                    null height 10
                    hbox:
                        null width 10
                        vbox:
                            null width 42
                            text "[y]"
                        hbox:
                            for x in range(0, lo.width()):
                                python:
                                    ui.imagebutton("tiles/emptyTile.png", "tiles/emptyTile.png", clicked=Function(registerClick, x, y))
                                #imagebutton:
                                #    idle "tiles/emptyTile.png"
                                #    hover "tiles/emptyTile.png"
                                #    action Function(registerClick, x, y)
                                null width 10
        bar value XScrollValue("gm") ysize 20
        vbar value YScrollValue("gm") xsize 20

screen disableGui:
    modal True
