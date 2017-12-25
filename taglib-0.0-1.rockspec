package = "taglib"
version = "0.0-1"
source = {
   url = "git://github.com/kedorlaomer/lua-taglib"
}
description = {
   summary = "Wrapper for taglib.",
   detailed = "This is a library for editing ID3 Tags, commonly used in MP3 files.",
   homepage = "http://github.com/kedorlaomer/lua-taglib",
   license = "LGPL3"
}
dependencies = {
   "lua >= 5.1"
}
build = {
   type = "builtin",
   modules = {
      taglib = {
         sources = {"src/taglib_lua.c"},
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
