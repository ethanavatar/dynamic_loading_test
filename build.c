#define  SELF_BUILD_C_
#include "self_build/self_build.h"

#define  ALL_STDLIB_C_
#include "self_build/all_stdlib.h"

static struct Build_Context_Options options = {
    .debug_info_kind = Debug_Info_Kind_Portable,
};

int main(void) {
    struct Thread_Context tctx = { 0 };
    thread_context_init_and_equip(&tctx);

    struct Allocator   allocator = scratch_begin(NULL);
    struct Build_Context context = build_create_context(options, ".", "bin", &allocator);
    
    bootstrap(&context, "build.c", "build.exe");

    struct Build lib = build_create(&context, Build_Kind_Shared_Library, "lib");
    list_append(&lib.sources, cstring_to_string("src/lib.c", &allocator));

    struct Build exe = build_create(&context, Build_Kind_Executable, "main");
    list_append(&exe.sources, cstring_to_string("src/main.c", &allocator));

    add_dependency(&exe, lib);
    build_module(&context, &exe);

    scratch_end(&allocator);
    thread_context_release();
    return 0;
}
