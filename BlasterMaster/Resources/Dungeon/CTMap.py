import bs4

with open('Map.tmx', 'r') as MapEditor:
  WorldMap = bs4.BeautifulSoup(''.join(MapEditor.readlines()), "xml")

WorldMap = WorldMap.find('map')
MAP_WIDTH = int(WorldMap['width']) * int(WorldMap['tilewidth'])
MAP_HEIGHT = int(WorldMap['height']) * int(WorldMap['tileheight'])
print("Width x Height =", MAP_WIDTH, MAP_HEIGHT)

def ReCoord(coord):
  X, Y, Width, Height = coord
  return X, MAP_HEIGHT - Y - Height, Width, Height

def GetDirect(GameObject: bs4.element.Tag):
  Direct = GameObject.find('property', attrs={'name': 'Direct'})
  if str(Direct) == 'None': return ""
  return ".{}".format(Direct["value"])

with open('Objects.ini', 'w') as conf:
  print('[OBJECTS]', file=conf)
  print('#', 'X', 'Y', 'WIDTH', 'HEIGHT', sep='\t', file=conf)

  # for ObjectName in ['Jason', 'Brick']:
  GameObjects = WorldMap.find_all('object') # , attrs={'name': ObjectName})
  GameObjects = map(lambda GameObject: [
    GameObject['name'], *ReCoord(list(map(int, [
      GameObject['x'], GameObject['y'],
      GameObject['width'], GameObject['height']]))),
    GetDirect(GameObject)], GameObjects)
  GameObjects = sorted(GameObjects)

  for name, X, Y, Width, Height, Direct in GameObjects:
    print(name.replace(' ', '-'), X, Y, Width, Height, sep='\t', file=conf)
