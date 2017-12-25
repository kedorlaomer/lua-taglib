#include <lauxlib.h>
#include <taglib/tag_c.h>

/*
 * Wrap taglib structures for usage with lua_newuserdata.
 */

typedef struct {
    TagLib_File *data;
} TagLib_File_wrapper;

typedef struct {
    TagLib_Tag *data;
} TagLib_Tag_wrapper;

static int lua_taglib_file_new(lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    TagLib_File *file = taglib_file_new(path);
    TagLib_File_wrapper *wrapper;
    wrapper = lua_newuserdata(L, sizeof(wrapper));
    luaL_getmetatable(L, "taglib.file");
    lua_setmetatable(L, -2);
    wrapper->data = file;
    return 1;
}

static int lua_taglib_file_tag(lua_State *L) {
    const TagLib_File_wrapper *file = luaL_checkudata(L, 1, "taglib.file");
    TagLib_Tag_wrapper *wrapper;
    TagLib_Tag *tag = taglib_file_tag(file->data);
    wrapper = lua_newuserdata(L, sizeof(wrapper));
    luaL_getmetatable(L, "taglib.tag");
    lua_setmetatable(L, -2);
    wrapper->data = tag;
    return 1;
}

/*
 * Factory for setters.
 */

#define define_lua_set_XXX(name)                                          \
static int lua_taglib_set_##name(lua_State *L) {                          \
    TagLib_Tag_wrapper *wrapper = luaL_checkudata(L, 1, "taglib.tag");    \
    const char *str = lua_tostring(L, 2);                                 \
    taglib_tag_set_##name(wrapper->data, str);                            \
    lua_pushnil(L);                                                       \
    return 1;                                                             \
}

/*
 * Factory for getters.
 */

#define define_lua_get_XXX(name)                                          \
static int lua_taglib_get_## name(lua_State *L) {                         \
    TagLib_Tag_wrapper *wrapper = luaL_checkudata(L, -1, "taglib.tag");   \
    char *str = taglib_tag_##name(wrapper->data);                         \
    lua_pushstring(L, str);                                               \
    taglib_free(str);                                                     \
    return 1;                                                             \
}

/*
 * Factory for both.
 */

#define create_functions(name) define_lua_get_XXX(name) define_lua_set_XXX(name)

/*
 * Still, we need to add them manually to the list in taglib_lib. TODO: year
 * and track are missing.
 */

create_functions(title)
create_functions(artist)
create_functions(album)
create_functions(comment)
create_functions(genre)

static int lua_taglib_file_save(lua_State *L) {
    const TagLib_File_wrapper *wrapper = luaL_checkudata(L, -1, "taglib.file");
    BOOL rv = taglib_file_save(wrapper->data);
    lua_pushboolean(L, rv);
    return 1;
}

static int lua_free_taglib_file(lua_State *L) {
    TagLib_File_wrapper *wrapper = lua_touserdata(L, 1);
    if (wrapper->data) taglib_file_free(wrapper->data);
    return 0;
}

static const struct luaL_Reg taglib_lib[] = {
    {"open", lua_taglib_file_new},
    {"tag", lua_taglib_file_tag},
    {"set_title", lua_taglib_set_title},
    {"set_artist", lua_taglib_set_artist},
    {"set_genre", lua_taglib_set_genre},
    {"set_comment", lua_taglib_set_comment},
    {"set_album", lua_taglib_set_album},
    {"get_title", lua_taglib_get_title},
    {"get_artist", lua_taglib_get_artist},
    {"get_genre", lua_taglib_get_genre},
    {"get_comment", lua_taglib_get_comment},
    {"get_album", lua_taglib_get_album},
    {"save", lua_taglib_file_save},
    {NULL, NULL}
};

int luaopen_taglib(lua_State *L) {
    luaL_newmetatable(L, "taglib.file");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, lua_free_taglib_file);
    lua_settable(L, -3);

    luaL_newmetatable(L, "taglib.tag");

    luaL_register(L, "taglib", taglib_lib);
    return 1;
}
