init -1:
    if(persistent.scripts is None):
        $ persistent.scripts = ""

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
        def tileChange(self, x, y, new):
            self.TileMap[y] = (self.TileMap[y])[:x] + new + (self.TileMap[y])[(x+1):]
            return True
