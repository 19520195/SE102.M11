from bs4 import BeautifulSoup, element
with open('Area3.tmx', 'r') as map_file:
  _map = BeautifulSoup(''.join(map_file.readlines()), "xml")

_map = _map.find('map')
MAP_WIDTH = int(_map['width']) * int(_map['tilewidth'])
MAP_HEIGHT = int(_map['height']) * int(_map['tileheight'])

bricks = _map.find('objectgroup', attrs={'name': 'Bricks'})
bricks = filter(lambda brick: type(brick) == element.Tag, bricks)
bricks = map(lambda brick: tuple(map(int, [
  brick['x'], brick['y'],
  brick['width'], brick['height']])), bricks)
bricks = sorted(bricks)

with open('Area3.ini', 'w') as conf:
  print('[OBJECTS]', file=conf)
  print('# 0 = Brick', file=conf)
  print('#', 'X', 'Y', 'WIDTH', 'HEIGHT', sep='\t', file=conf)
  for x, y, width, height in bricks:
    y = MAP_HEIGHT - y - height
    print(0, x, y, width, height, sep='\t', file=conf)
