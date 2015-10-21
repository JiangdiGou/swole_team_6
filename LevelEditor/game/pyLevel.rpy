init:
    $ config.keymap['viewport_up'].append('K_UP')
    $ config.keymap['viewport_up'].append('repeat_K_UP')
    $ config.keymap['viewport_down'].append('K_DOWN')
    $ config.keymap['viewport_down'].append('repeat_K_DOWN')

init -2 python:
    import os
    def registerClick(x, y):
        renpy.log(str(x) + "," + str(y))
        guiView.x = x
        guiView.y = y
        renpy.jump("loop1")


init python:
    class Entity:
        x = -1.1
        y = -1.1
        name = ""
        components = []
        def __init__(self):
            return

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
        EntityList = [[]]

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

            file.write("%s\n" % "[EntityList]")
            for entity in self.EntityList:
                if entity == []:
                    return
                file.write("%s " % entity.name)
                file.write("at (%f, %f)\n" % x, y)
                for component in entity.components:
                    file.write("%s\n", component)

            return
        def height(self):
            return int(self.ArrayHeight)
        def width(self):
            return int(self.ArrayWidth)

init python:
    # actually make this its own library later >:)
    # renpytom said we shouldn't do this...
    def modright(obj):
        step = obj.xadjustment.get_step()
        oldval = obj.xadjustment.get_value()
        obj.xadjustment.change(oldval + step)
    def modleft(obj):
        step = obj.xadjustment.get_step()
        oldval = obj.xadjustment.get_value()
        obj.xadjustment.change(oldval - step)

screen gui_menu(lo, vi):
    #leftside
    frame:
        ysize (config.screen_height - 250)
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
                hbox:
                    null width 64
                    for x in range(0, lo.width()):
                        vbox:
                            null width 64
                            text "[x]"  
                ysize (lo.height() * 64)
                for y in range(0, lo.height()):
                    hbox:
                        vbox:
                            $ realy = lo.height() - y
                            null width 64
                            text "[realy]"
                        hbox:
                            for x in range(0, lo.width()):
                                python:
                                    ui.imagebutton("tiles/emptyTile64.png", "tiles/emptyTile64.png", clicked=Function(registerClick, x, y))
                                #imagebutton:
                                #    idle "tiles/emptyTile.png"
                                #    hover "tiles/emptyTile.png"
                                #    action Function(registerClick, x, y)
        bar value XScrollValue("gm") ysize 20
        vbar value YScrollValue("gm") xsize 20
        $ local = renpy.get_widget(None, "gm")
        key "input_right" action [[Function(modright, local)]]
        key "input_left" action [[Function(modleft, local)]]

screen disableGui:
    modal True
    textbutton "Never Mind":
        xalign 0.5
        yalign 0.7
        action Jump("loop1")
