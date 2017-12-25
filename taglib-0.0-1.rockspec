package = "taglib"
version = "0.0-1"
source = {
   url = "src" -- "git://github.com/kedorlaomer/lua-id3v2"
}
description = {
   summary = "Wrapper for taglib.",
   detailed = "This is a library for editing ID3 Tags, rev. 2.4, commonly used in MP3 files.",
   homepage = "http://github.com/kedorlaomer/id3v2lib_lua",
   license = "LGPL3"
}
dependencies = {
   "lua ~> 5.1"
}
build = {
   type = "builtin",
   modules = {
      taglib = {
         sources = {"taglib_lua.c"},
         libraries = {"tag_c"}
      }
   }
}
external_dependencies = {
    TAGLIB = {
        header = "taglib/tag_c.h",
        library = "libtag_c.so"
    }
}
