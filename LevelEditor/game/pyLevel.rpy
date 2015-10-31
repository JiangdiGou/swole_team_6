init -1:
    if(persistent.scripts is None):
        $ persistent.scripts = ""

init python:
    import copy

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
        preset = 1
        def __init__(self):
            return

    class Level:
        FileLoc = ""
        LevelName = ""
        ArrayWidth = 0
        ArrayHeight = 0
        TileMap = []
        EntityList = [[]]
        UndoState = None
        UsableState = False

        def __init__(self):
            return

        def initFile(self):
            try:
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
                for line in reversed(self.TileMap):
                    file.write("%s\n" % line)

                file.write("%s\n" % "[EntityList]")
                for entity in self.EntityList:
                    if entity == []:
                        return
                    file.write("%s " % entity.name)
                    file.write("at (%f, %f)\n" % x, y)
                    for component in entity.components:
                        file.write("%s\n", component)
                file.close()
                self.UsableState = True
            except:
                self.UsableState = False

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
            for line in reversed(self.TileMap):
                file.write("%s\n" % line)

            file.write("%s\n" % "[EntityList]")
            for entity in self.EntityList:
                if entity == []:
                    return
                file.write("%s " % entity.name)
                file.write("at (%f, %f)\n" % x, y)
                for component in entity.components:
                    file.write("%s\n", component)
            file.close()

        def loadFrom(self, uiFile):
            try:
                self.FileLoc = uiFile
                file = open(self.FileLoc, 'r')
                counter = 0
                lineTile = 0
                allLines = list(file)
                tempList = []

                for line in allLines:
                    if(counter == 1):
                        self.LevelName = line
                    elif(counter == 3):
                        self.ArrayWidth = line
                    elif(counter == 4):
                        self.ArrayHeight = line
                    elif(counter > 5 and line != "[EntityList]" and lineTile < int(self.ArrayHeight)):
                        self.TileMap.append(line)
                        lineTile += 1
                    counter += 1
                self.TileMap.reverse()
                file.close()
                self.UsableState = True
            except:
                self.UsableState = False

        def height(self):
            return int(self.ArrayHeight)
        def width(self):
            return int(self.ArrayWidth)

        def tileChange(self, x, y, new):
            self.TileMap[y] = (self.TileMap[y])[:x] + new + (self.TileMap[y])[(x+1):]
            return True
        def insert(self, typeloc, where):
            count = 0
            if(typeloc == "left"):
                self.ArrayWidth = str(self.width() + 1)
                for line in self.TileMap:
                    self.TileMap[count] = line[:where] + '0' + line[where:]
                    count += 1
                return
            if(typeloc == "right"):
                self.ArrayWidth = str(self.width() + 1)
                where += 1
                for line in self.TileMap:
                    self.TileMap[count] = line[:where] + '0' + line[where:]
                    count += 1
                return
            if(typeloc == "up"):
                self.ArrayHeight = str(self.height() + 1)
                self.TileMap.insert(where + 1, "0"*(int(self.ArrayWidth)))
                return
            if(typeloc == "down"):
                self.ArrayHeight = str(self.height() + 1)
                self.TileMap.insert(where, "0"*(int(self.ArrayWidth)))
                return

        def saveState(self):
            self.UndoState = copy.deepcopy(self)
            self.UndoState.TileMap = copy.deepcopy(self.TileMap)
