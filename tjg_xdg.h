#ifndef TJG_XDG_H_
#define TJG_XDG_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *tjg_xdg_data_home(void);
char *tjg_xdg_config_home(void);
char *tjg_xdg_state_home(void);
//TODO: char *tjg_xdg_data_dirs(void);
//TODO: char *tjg_xdg_config_dirs(void);
char *tjg_xdg_cache_home(void);
char *tjg_xdg_runtime_dir(void);

#endif // TJG_XDG_H_


#ifdef TJG_XDG_IMPLEMENTATION

bool tjg_xdg__path_is_absolute(const char *path) {
    return path[0] == '/';
}

const char *tjg_xdg__user_home(void) {
    // TODO: `HOME` envariable might not be set!
    return getenv("HOME");
}

char *tjg_xdg__base_dir(const char *envar, const char *default_dir) {
    char *base_dir = NULL;

    const char *base_dir_env = getenv(envar);
    if (base_dir_env && tjg_xdg__path_is_absolute(base_dir_env)) {
        base_dir = strdup(base_dir_env);
    } else if (default_dir) {
        const char *user_home = tjg_xdg__user_home();
        if (user_home && tjg_xdg__path_is_absolute(user_home)) {
            base_dir = malloc(strlen(user_home) + strlen(default_dir) + 1);
            strcpy(base_dir, user_home);
            strcat(base_dir, default_dir);
        }
    }

    return base_dir;
}


char *tjg_xdg_data_home(void) {
    return tjg_xdg__base_dir("XDG_DATA_HOME", "/.local/share");
}

char *tjg_xdg_config_home(void) {
    return tjg_xdg__base_dir("XDG_CONFIG_HOME", "/.config");
}

char *tjg_xdg_state_home(void) {
    return tjg_xdg__base_dir("XDG_STATE_HOME", "/.local/state");
}

char *tjg_xdg_cache_home(void) {
    return tjg_xdg__base_dir("XDG_CACHE_HOME", "/.cache");
}

char *tjg_xdg_runtime_dir(void) {
    return tjg_xdg__base_dir("XDG_RUNTIME_DIR", NULL);
}

#endif // TJG_XDG_IMPLEMENTATION


#ifdef TJG_STRIP_PREFIX
    #define xdg_data_home tjg_xdg_data_home
    #define xdg_config_home tjg_xdg_config_home
    #define xdg_state_home tjg_xdg_state_home
    #define xdg_cache_home tjg_xdg_cache_home
    #define xdg_runtime_dir tjg_xdg_runtime_dir
#endif // TJG_STRIP_PREFIX
