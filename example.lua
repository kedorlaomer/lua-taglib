-- the example covers the whole API wrapped by this rock :-(

taglib = require 'taglib'
fname = 'some_mp3_file.mp3'
file = taglib.open(fname)
tag = taglib.tag(file)
print('title: ' .. taglib.get_title(tag))
taglib.set_title(tag, 'A new title')
print('comment: ' .. taglib.get_comment(tag))
taglib.set_comment(tag, 'A new comment')
print('album: ' .. taglib.get_album(tag))
taglib.set_album(tag, 'A new album')
print('genre: ' .. taglib.get_genre(tag))
taglib.set_genre(tag, 'A new genre')
print('artist: ' .. taglib.get_artist(tag))
taglib.set_artist(tag, 'A new artist')
taglib.save(file)
