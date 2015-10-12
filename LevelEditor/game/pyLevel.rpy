init -2 python:
    import os
    def registerClick(x, y):
        renpy.log(str(x) + "," + str(y))


init python:
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

screen gui_menu(lo):
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
                    null width 74
                    for x in range(0, lo.width()):
                        vbox:
                            null width 74
                            text "[x]"  
                ysize (lo.height() * 74)
                for y in range(0, lo.height()):
                    null height 10
                    hbox:
                        null width 10
                        vbox:
                            null width 74
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
