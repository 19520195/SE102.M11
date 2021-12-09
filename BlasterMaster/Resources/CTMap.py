from bs4 import BeautifulSoup, element
with open('Area3.tmx', 'r') as map_file:
  _map = BeautifulSoup(''.join(map_file.readlines()), "xml")

_map = _map.find('map')
MAP_WIDTH = int(_map['width']) * int(_map['tilewidth'])
MAP_HEIGHT = int(_map['height']) * int(_map['tileheight'])

with open('Area3.2.ini', 'w') as conf:
  print('[OBJECTS]', file=conf)
  print('#', 'X', 'Y', 'WIDTH', 'HEIGHT', sep='\t', file=conf)

  for object_name in ['SophiaIII', 'Brick', 'Ball Carry', 'Ballbot', 'Eyelet', 'Interrupt', 'Stuka']:
    game_object = _map.find_all('object', attrs={'name': object_name})
    game_object = map(lambda object: tuple(map(int, [
      object['x'], object['y'],
      object['width'], object['height']])), game_object)
    game_object = sorted(game_object)

    object_name = object_name.replace(' ', '-')
    for x, y, width, height in game_object:
      y = MAP_HEIGHT - y - height
      print(object_name, x, y, width, height, sep='\t', file=conf)
