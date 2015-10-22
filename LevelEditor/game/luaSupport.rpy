init -1:
    $ luaChars = ['0']
    $ luaTiles = []

init python:
    import lupa
    import os
    def scriptsToRegistrar(folder):
        abspathTiles = os.path.abspath(folder + "/TileArchetypes")
        for filename in os.listdir(abspathTiles):
            if not filename.endswith(".lua"):
                continue
            luaScript = os.path.abspath(abspathTiles + "/" + filename)
            L = lupa.LuaRuntime(unpack_returned_tuples=False)
            luaCode = file(luaScript).read().decode("utf-8")
            L.execute(luaCode)
            thisChar = L.globals().character
            luaChars.extend(thisChar)
            luaTiles.append([L.globals().aType.name, thisChar])
        luaRegistrar = [[]]
        return luaRegistrar