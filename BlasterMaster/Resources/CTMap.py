import bs4

with open('Area3.tmx', 'r') as MapEditor:
  WorldMap = bs4.BeautifulSoup(''.join(MapEditor.readlines()), "xml")

WorldMap = WorldMap.find('map')
MAP_WIDTH = int(WorldMap['width']) * int(WorldMap['tilewidth'])
MAP_HEIGHT = int(WorldMap['height']) * int(WorldMap['tileheight'])

def ReCoord(coord):
  X, Y, Width, Height = coord
  return X, MAP_HEIGHT - Y - Height, Width, Height

def GetRefer(GameObject: bs4.element.Tag):
  Refer = GameObject.find('property', attrs={'name': 'Trigger'})
  if str(Refer) == 'None': return None
  ID = Refer['value']

  Refer = WorldMap.find('object', attrs={'id': ID})
  return ReCoord(tuple(map(int, (Refer['x'], Refer['y'], Refer['width'], Refer['height']))))

with open('Area3.2.ini', 'w') as conf:
  print('[OBJECTS]', file=conf)
  print('#', 'X', 'Y', 'WIDTH', 'HEIGHT', sep='\t', file=conf)

  for ObjectName in ['SophiaIII', 'Brick', 'Ball Carry', 'Ballbot', 'Eyelet', 'Interrupt', 'Stuka']:
    GameObjects = WorldMap.find_all('object', attrs={'name': ObjectName})
    GameObjects = map(lambda GameObject: [*ReCoord(list(map(int, [
      GameObject['x'], GameObject['y'],
      GameObject['width'], GameObject['height']]))), GetRefer(GameObject)], GameObjects)
    GameObjects = sorted(GameObjects)

    ObjectName = ObjectName.replace(' ', '-')
    for X, Y, Width, Height, Refer in GameObjects:
      Refer = '{}\t{}\t{}\t{}'.format(*Refer) if Refer else ''
      print(ObjectName, X, Y, Width, Height, Refer, sep='\t', file=conf)
