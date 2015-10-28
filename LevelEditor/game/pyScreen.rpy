init -2:
    $ config.keymap.update({"input_up":[ 'K_UP', 'repeat_K_UP' ]})
    $ config.keymap.update({"input_down":[ 'K_DOWN', 'repeat_K_DOWN' ]})

init -2 python:
    import os
    def registerClick(x, y):
        renpy.log(str(x) + "," + str(y))
        guiView.x = x
        guiView.y = y
        renpy.jump("loop1")

init python:
    def modright(obj):
        step = obj.xadjustment.get_step()
        oldval = obj.xadjustment.get_value()
        obj.xadjustment.change(oldval + step)
    def modleft(obj):
        step = obj.xadjustment.get_step()
        oldval = obj.xadjustment.get_value()
        obj.xadjustment.change(oldval - step)
    def modup(obj):
        step = obj.yadjustment.get_step()
        oldval = obj.yadjustment.get_value()
        obj.yadjustment.change(oldval - step)
    def moddown(obj):
        step = obj.yadjustment.get_step()
        oldval = obj.yadjustment.get_value()
        obj.yadjustment.change(oldval + step)

init python:
    adj=ui.adjustment()
    def askTile(tiles):
        menu_answers = []
        for tile in tiles:
            menu_answers.append((tile[0], tile[1]))
        q = []
        q.extend(menu_answers)
        return menu(q, screen="packedMenu")

screen packedMenu:
    zorder 2
    modal True
    window:
        style "menu_window"
        xalign 0.5
        ymaximum 400
        xsize 590
        side "c r":
            frame:
                has viewport:
                    mousewheel True
                    draggable True
                    yinitial 0.0
                    yadjustment adj
                vbox:
                    style "menu"
                    spacing 2
                    for caption, action, chosen in items:

                        if action:

                            button:
                                action action
                                style "menu_choice_button"
                                text caption style "menu_choice"

                        else:
                            text caption style "menu_caption"
            bar adjustment adj style 'vscrollbar'

screen vpkm(obj):
    $ local = renpy.get_widget(None, obj)
    key "input_right" action [[Function(modright, local)]]
    key "input_left" action [[Function(modleft, local)]]
    key "input_up" action [[Function(modup, local)]]
    key "input_down" action [[Function(moddown, local)]]

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
            text "Character:"
            if(vi.x == -1 or vi.y == -1):
                textbutton "Bad Tile"
            else:
                $ tile = (lo.TileMap[vi.y])[vi.x]
                textbutton "[tile]" xalign 0.5 action Jump("changeTile")

            text "Toolbox:"
            textbutton "Undo" xalign 0.5 action Jump("doUndo")
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
                            $ realy = lo.height() - y - 1
                            null width 64
                            text "[realy]"
                        hbox:
                            for x in range(0, lo.width()):
                                python:
                                    ui.imagebutton("tiles/emptyTile64.png", "tiles/emptyTile64.png", clicked=Function(registerClick, x, realy))
                                #imagebutton:
                                #    idle "tiles/emptyTile.png"
                                #    hover "tiles/emptyTile.png"
                                #    action Function(registerClick, x, y)
        bar value XScrollValue("gm") ysize 20
        vbar value YScrollValue("gm") xsize 20
    use vpkm("gm")

screen disableGui:
    modal True
    textbutton "Never Mind":
        xalign 0.5
        yalign 0.7
        action Jump("loop1")

screen understood:
    modal True
    zorder 1
    textbutton "Sorry!":
        xalign 0.5
        yalign 0.9
        action Jump("loop1")
