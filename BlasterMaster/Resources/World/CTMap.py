import bs4

with open('Map.tmx', 'r') as MapEditor:
  WorldMap = bs4.BeautifulSoup(''.join(MapEditor.readlines()), "xml")

WorldMap = WorldMap.find('map')
MAP_WIDTH = int(WorldMap['width']) * int(WorldMap['tilewidth'])
MAP_HEIGHT = int(WorldMap['height']) * int(WorldMap['tileheight'])

def ReCoord(coord):
  X, Y, Width, Height = coord
  return X, MAP_HEIGHT - Y - Height, Width, Height

def GetDirect(GameObject: bs4.element.Tag):
  Direct = GameObject.find('property', attrs={'name': 'Direct'})
  if str(Direct) == 'None': return ""
  return ".{}".format(Direct["value"])

with open('_Objects.ini', 'w') as conf:
  print('[OBJECTS]', file=conf)
  print('#', 'X', 'Y', 'WIDTH', 'HEIGHT', sep='\t', file=conf)

  for ObjectName in ['SophiaIII', 'Scene Portal', 'Brick', 'Ball Carry', 'Ballbot', 'Eyelet', 'Interrupt', 'Stuka']:
    GameObjects = WorldMap.find_all('object', attrs={'name': ObjectName})
    GameObjects = map(lambda GameObject: [*ReCoord(list(map(int, [
      GameObject['x'], GameObject['y'],
      GameObject['width'], GameObject['height']]))), GetDirect(GameObject)], GameObjects)
    GameObjects = sorted(GameObjects)

    ObjectName = ObjectName.replace(' ', '-')
    for X, Y, Width, Height, Direct in GameObjects:
      print(ObjectName + Direct, X, Y, Width, Height, sep='\t', file=conf)
