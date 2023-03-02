#define HL_NAME(n) hlSokol##n

#include "hl.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <cstring>
#include "d3d11entry.h"
#define SOKOL_DLL
#define SOKOL_IMPL
#define SOKOL_D3D11
#define SOKOL_LOG(s) OutputDebugStringA(s)
#include "sokol_gfx.h"
#include "sokol_fetch.h"
//#include "sokol_log.h"
#include "sokol_glue.h"
#include "sokol_gp.h"
#include "sokol_gl.h"
#include "sokol_app.h"
#include "sokol_glue.h"
#include "sokol_debugtext.h"
#define FONTSTASH_IMPLEMENTATION
#if defined(_MSC_VER )
#pragma warning(disable:4996)   // strncpy use in fontstash.h
#endif
#include "fontstash.h"
#define SOKOL_FONTSTASH_IMPL
#include "sokol_fontstash.h"
//#include "dbgui/dbgui.h"
#include "fileutil.h"

#define FONT_KC853 (0)
#define FONT_KC854 (1)
#define FONT_Z1013 (2)
#define FONT_CPC   (3)
#define FONT_C64   (4)
#define FONT_ORIC  (5)

/////////////////////////////////////////////////////////////////////////////////////

wchar_t* cStrToWChar(char* str)
{
    wchar_t* vOut = new wchar_t[strlen(str) + 1];
    mbstowcs_s(NULL, vOut, strlen(str) + 1, str, strlen(str));
    return vOut;
}

float* varrToFloats(varray* arr) { return (float*)(hl_aptr(arr, float)); }
int* varrToInts(varray* arr) { return (int*)(hl_aptr(arr, int)); }
char** varrToChars(varray* arr) { return (char**)(hl_aptr(arr, char*)); }

/* round to next power of 2 (see bit-twiddling-hacks) */
static int round_pow2(float v) {
    uint32_t vi = ((uint32_t)v) - 1;
    for (uint32_t i = 0; i < 5; i++) {
        vi |= (vi >> (1 << i));
    }
    return (int)(vi + 1);
}

struct Doh
{
    float x;
    float y;
};

struct Test123
{
    char* myStr;
    int myInt;
    float myFloat;
    varray* vals;
    varray* valz;
    Doh* doh;
};

HL_PRIM void HL_NAME(test)(Test123* tstruct)
{
    int myi = tstruct->myInt;

    float* i = varrToFloats(tstruct->vals);
    char** s = varrToChars(tstruct->valz);
    auto v0 = i[0];
    auto v1 = i[1];
    auto v2 = i[2];
    auto v3 = i[3];

    auto s0 = s[0];
    auto s1 = s[1];
    auto s2 = s[2];

    auto d0 = tstruct->doh->x;
    auto d1 = tstruct->doh->y;
    float myf = tstruct->myFloat;

} DEFINE_PRIM(_VOID, test, _STRUCT);

HL_PRIM void HL_NAME(d3dInit)(int width, int height, int samplecount, char* title) { d3d11_init(width, height, samplecount, cStrToWChar(title)); } DEFINE_PRIM(_VOID, d3dInit, _I32 _I32 _I32 _BYTES);
HL_PRIM bool HL_NAME(d3d11ProcessEvents)() { return d3d11_process_events(); } DEFINE_PRIM(_BOOL, d3d11ProcessEvents, _NO_ARG);
HL_PRIM void HL_NAME(sgBeginDefaultPass)(int width, int height) { sg_pass_action pass_action = { 0 }; sg_begin_default_pass(&pass_action, width, height); } DEFINE_PRIM(_VOID, sgBeginDefaultPass, _I32 _I32);
HL_PRIM void HL_NAME(sgSetup)() { sg_desc desc = { .context = sapp_sgcontext()/*d3d11_get_context()*/ }; sg_setup(&desc); } DEFINE_PRIM(_VOID, sgSetup, _NO_ARG);
HL_PRIM void HL_NAME(sgEndPass)() { sg_end_pass(); } DEFINE_PRIM(_VOID, sgEndPass, _NO_ARG);
HL_PRIM void HL_NAME(sgCommit)() { sg_commit(); } DEFINE_PRIM(_VOID, sgCommit, _NO_ARG);
HL_PRIM sg_buffer HL_NAME(sgMakeBuffer)(varray* vertices)
{
    float* verts = *((float**)(hl_aptr(vertices, float*)));
    sg_buffer_desc buf = { .data = SG_RANGE(verts) };
    sg_buffer vbuf = sg_make_buffer(&buf);
    return vbuf;
} DEFINE_PRIM(_STRUCT, sgMakeBuffer, _ARR );

HL_PRIM sg_shader HL_NAME(sgMakeShader)()
{
    sg_shader_desc shdesc = {};
    shdesc.attrs[0].sem_name = "POS";
    shdesc.attrs[1].sem_name = "COLOR";
    shdesc.vs.source =
        "struct vs_in {\n"
        "  float4 pos: POS;\n"
        "  float4 color: COLOR;\n"
        "};\n"
        "struct vs_out {\n"
        "  float4 color: COLOR0;\n"
        "  float4 pos: SV_Position;\n"
        "};\n"
        "vs_out main(vs_in inp) {\n"
        "  vs_out outp;\n"
        "  outp.pos = inp.pos;\n"
        "  outp.color = inp.color;\n"
        "  return outp;\n"
        "}\n";
    shdesc.fs.source =
        "float4 main(float4 color: COLOR0): SV_Target0 {\n"
        "  return color;\n"
        "}\n";
    sg_shader shd = sg_make_shader(shdesc);
    return shd;
    
} DEFINE_PRIM(_STRUCT, sgMakeShader, _NO_ARG );

HL_PRIM sg_pipeline HL_NAME(sgMakePipeline)(sg_shader shd)
{
    sg_pipeline_desc pipdesc = {};
    pipdesc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
    pipdesc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT4;
    pipdesc.shader = shd;
    return sg_make_pipeline(pipdesc);
    
} DEFINE_PRIM(_STRUCT, sgMakePipeline, _STRUCT );
HL_PRIM void HL_NAME(sgApplyPipeline)(sg_pipeline pipeline) { sg_apply_pipeline(pipeline); } DEFINE_PRIM(_VOID, sgApplyPipeline, _STRUCT);
HL_PRIM void HL_NAME(sgApplyBindings)(const sg_bindings bind) { sg_apply_bindings(&bind); } DEFINE_PRIM(_VOID, sgApplyBindings, _STRUCT);
HL_PRIM void HL_NAME(sgDraw)(int base_element, int num_elements, int num_instances) { sg_draw(base_element, num_elements, num_instances); } DEFINE_PRIM(_VOID, sgDraw, _I32 _I32 _I32);
HL_PRIM int HL_NAME(roundPow2)(float v) { return round_pow2(v); } DEFINE_PRIM(_I32, roundPow2, _F32);

HL_PRIM void HL_NAME(d3d11Present)() { d3d11_present(); } DEFINE_PRIM(_VOID, d3d11Present, _NO_ARG);
HL_PRIM void HL_NAME(sgShutdown)() { sg_shutdown(); } DEFINE_PRIM(_VOID, sgShutdown, _NO_ARG);
HL_PRIM void HL_NAME(d3d11Shutdown)() { d3d11_shutdown(); } DEFINE_PRIM(_VOID, d3d11Shutdown, _NO_ARG);
HL_PRIM int HL_NAME(d3d11Width)() { return d3d11_width(); } DEFINE_PRIM(_I32, d3d11Width, _NO_ARG);
HL_PRIM int HL_NAME(d3d11Height)() { return d3d11_height(); } DEFINE_PRIM(_I32, d3d11Height, _NO_ARG);


HL_PRIM int HL_NAME(sAppWidth)() { return sapp_width(); } DEFINE_PRIM(_I32, sAppWidth, _NO_ARG);
HL_PRIM int HL_NAME(sAppHeight)() { return sapp_height(); } DEFINE_PRIM(_I32, sAppHeight, _NO_ARG);
HL_PRIM bool HL_NAME(sAppIsFullscreen)() { return sapp_is_fullscreen(); } DEFINE_PRIM(_BOOL, sAppIsFullscreen, _NO_ARG);
HL_PRIM void HL_NAME(sAppToggleFullscreen)() { sapp_toggle_fullscreen(); } DEFINE_PRIM(_VOID, sAppToggleFullscreen, _NO_ARG);

// Initialize Sokol GP, adjust the size of command buffers for your own use.
HL_PRIM void HL_NAME(sgpSetup)(){ sgp_desc sgpdesc = { 0 }; sgp_setup(&sgpdesc); } DEFINE_PRIM(_VOID, sgpSetup, _NO_ARG);
HL_PRIM void HL_NAME(sgpShutdown)() { sgp_shutdown(); } DEFINE_PRIM(_VOID, sgpShutdown, _NO_ARG);
HL_PRIM bool HL_NAME(sgpIsValid)() { return sgp_is_valid(); } DEFINE_PRIM(_BOOL, sgpIsValid, _NO_ARG);

HL_PRIM sgp_error HL_NAME(sgpGetLastError)() { return sgp_get_last_error(); } DEFINE_PRIM(_I32, sgpGetLastError, _NO_ARG);
HL_PRIM const char* HL_NAME(sgpGetErrorMessage)(sgp_error error) { return sgp_get_error_message(error); } DEFINE_PRIM(_BYTES, sgpGetErrorMessage, _I32);

HL_PRIM sg_pipeline HL_NAME(sgpMakePipeline)(const sgp_pipeline_desc desc) { return sgp_make_pipeline(&desc); } DEFINE_PRIM(_STRUCT, sgpMakePipeline, _STRUCT);

HL_PRIM void HL_NAME(sgpBegin)(int width, int height) { sgp_begin(width, height); } DEFINE_PRIM(_VOID, sgpBegin, _I32 _I32);
HL_PRIM void HL_NAME(sgpFlush)() { sgp_flush(); } DEFINE_PRIM(_VOID, sgpFlush, _NO_ARG);
HL_PRIM void HL_NAME(sgpEnd)() { sgp_end(); } DEFINE_PRIM(_VOID, sgpEnd, _NO_ARG);

HL_PRIM void HL_NAME(sgpProject)(float left, float right, float top, float bottom) { sgp_project(left, right, top, bottom); } DEFINE_PRIM(_VOID, sgpProject, _F32 _F32 _F32 _F32);
HL_PRIM void HL_NAME(sgpResetProject)() { sgp_reset_project(); } DEFINE_PRIM(_VOID, sgpResetProject, _NO_ARG);

HL_PRIM void HL_NAME(sgpPushTransform)() { sgp_push_transform(); } DEFINE_PRIM(_VOID, sgpPushTransform, _NO_ARG);
HL_PRIM void HL_NAME(sgpPopTransform)() { sgp_pop_transform(); } DEFINE_PRIM(_VOID, sgpPopTransform, _NO_ARG);
HL_PRIM void HL_NAME(sgpResetTransform)() { sgp_reset_transform(); } DEFINE_PRIM(_VOID, sgpResetTransform, _NO_ARG);
HL_PRIM void HL_NAME(sgpTranslate)(float x, float y) { sgp_translate(x, y); } DEFINE_PRIM(_VOID, sgpTranslate, _F32 _F32);
HL_PRIM void HL_NAME(sgpRotate)(float theta) { sgp_rotate(theta); } DEFINE_PRIM(_VOID, sgpRotate, _F32);
HL_PRIM void HL_NAME(sgpRotateAt)(float theta, float x, float y) { sgp_rotate_at(theta, x, y); } DEFINE_PRIM(_VOID, sgpRotateAt, _F32 _F32 _F32);
HL_PRIM void HL_NAME(sgpScale)(float sx, float sy) { sgp_scale(sx, sy); } DEFINE_PRIM(_VOID, sgpScale, _F32 _F32);
HL_PRIM void HL_NAME(sgpScaleAt)(float sx, float sy, float x, float y) { sgp_scale_at(sx, sy, x, y); } DEFINE_PRIM(_VOID, sgpScaleAt, _F32 _F32 _F32 _F32);

HL_PRIM void HL_NAME(sgpSetPipeline)(sg_pipeline pipeline) { return sgp_set_pipeline(pipeline); } DEFINE_PRIM(_VOID, sgpSetPipeline, _STRUCT);
HL_PRIM void HL_NAME(sgpResetPipeline)() { sgp_reset_pipeline(); } DEFINE_PRIM(_VOID, sgpResetPipeline, _NO_ARG);
HL_PRIM void HL_NAME(sgpSetUniform)(const void* data, uint32_t size) { sgp_set_uniform(data, size); } DEFINE_PRIM(_VOID, sgpSetUniform, _BYTES _I32);
HL_PRIM void HL_NAME(sgpResetUniform)() { sgp_reset_uniform(); } DEFINE_PRIM(_VOID, sgpResetUniform, _NO_ARG);

HL_PRIM void HL_NAME(sgpSetBlendMode)(sgp_blend_mode blendmode) { sgp_set_blend_mode(blendmode); } DEFINE_PRIM(_VOID, sgpSetBlendMode, _I32);
HL_PRIM void HL_NAME(sgpResetBlendMode)() { sgp_reset_blend_mode(); } DEFINE_PRIM(_VOID, sgpResetBlendMode, _NO_ARG);
HL_PRIM void HL_NAME(sgpSetColor)(double r, double g, double b, double a) { sgp_set_color(r,g,b,a); } DEFINE_PRIM(_VOID, sgpSetColor, _F64 _F64 _F64 _F64);
HL_PRIM void HL_NAME(sgpResetColor)() { sgp_reset_color(); } DEFINE_PRIM(_VOID, sgpResetColor, _NO_ARG);
HL_PRIM void HL_NAME(sgpSetImage)(int channel, sg_image image) { sgp_set_image(channel,image); } DEFINE_PRIM(_VOID, sgpSetImage, _I32 _STRUCT);
HL_PRIM void HL_NAME(sgpUnsetImage)(int channel) { sgp_unset_image(channel); } DEFINE_PRIM(_VOID, sgpUnsetImage, _I32 );
HL_PRIM void HL_NAME(sgpResetImage)(int channel) { sgp_reset_image(channel); } DEFINE_PRIM(_VOID, sgpResetImage, _I32 );

HL_PRIM void HL_NAME(sgpViewport)(int x, int y, int w, int h) { sgp_viewport(x, y, w, h); } DEFINE_PRIM(_VOID, sgpViewport, _I32 _I32 _I32 _I32);
HL_PRIM void HL_NAME(sgpResetViewport)() { sgp_reset_viewport(); } DEFINE_PRIM(_VOID, sgpResetViewport, _NO_ARG);
HL_PRIM void HL_NAME(sgpScissor)(int x, int y, int w, int h) { sgp_scissor(x, y, w, h); } DEFINE_PRIM(_VOID, sgpScissor, _I32 _I32 _I32 _I32);
HL_PRIM void HL_NAME(sgpResetScissor)() { sgp_reset_scissor(); } DEFINE_PRIM(_VOID, sgpResetScissor, _NO_ARG);
HL_PRIM void HL_NAME(sgpResetState)() { sgp_reset_state(); } DEFINE_PRIM(_VOID, sgpResetState, _NO_ARG);

HL_PRIM void HL_NAME(sgpClear)() { sgp_clear(); } DEFINE_PRIM(_VOID, sgpClear, _NO_ARG);
HL_PRIM void HL_NAME(sgpDrawPoints)(varray* points, uint32_t count) { sgp_draw_points(*((sgp_point**)(hl_aptr(points, sgp_point*))),count); } DEFINE_PRIM(_VOID, sgpDrawPoints, _ARR _I32);
HL_PRIM void HL_NAME(sgpDrawPoint)(float x, float y) { sgp_draw_point(x,y); } DEFINE_PRIM(_VOID, sgpDrawPoint, _F32 _F32);
HL_PRIM void HL_NAME(sgpDrawLines)(const sgp_line* lines, uint32_t count) { sgp_draw_lines(*((sgp_line**)(hl_aptr(lines, sgp_line*))), count); } DEFINE_PRIM(_VOID, sgpDrawLines, _ARR _I32);
HL_PRIM void HL_NAME(sgpDrawLine)(float ax, float ay, float bx, float by) { sgp_draw_line(ax, ay, bx, by); } DEFINE_PRIM(_VOID, sgpDrawLine, _F32 _F32 _F32 _F32);
HL_PRIM void HL_NAME(sgpDrawLinesStrip)(const sgp_point* points, uint32_t count) { sgp_draw_lines_strip(*((sgp_point**)(hl_aptr(points, sgp_point*))), count); } DEFINE_PRIM(_VOID, sgpDrawLinesStrip, _ARR _I32);
HL_PRIM void HL_NAME(sgpDrawFilledTriangles)(const sgp_triangle* triangles, uint32_t count) { sgp_draw_filled_triangles(*((sgp_triangle**)(hl_aptr(triangles, sgp_triangle*))), count); } DEFINE_PRIM(_VOID, sgpDrawFilledTriangles, _ARR _I32);
HL_PRIM void HL_NAME(sgpDrawFilledTriangle)(float ax, float ay, float bx, float by, float cx, float cy) { sgp_draw_filled_triangle(ax, ay, bx, by, cx, cy); } DEFINE_PRIM(_VOID, sgpDrawFilledTriangle, _F32 _F32 _F32 _F32 _F32 _F32);
HL_PRIM void HL_NAME(sgpDrawFilledTrianglesStrip)(const sgp_point* points, uint32_t count) { sgp_draw_filled_triangles_strip(*((sgp_point**)(hl_aptr(points, sgp_point*))), count); } DEFINE_PRIM(_VOID, sgpDrawFilledTrianglesStrip, _ARR _I32);
HL_PRIM void HL_NAME(sgpDrawFilledRects)(const sgp_rect* rects, uint32_t count) { sgp_draw_filled_rects(*((sgp_rect**)(hl_aptr(rects, sgp_rect*))), count); } DEFINE_PRIM(_VOID, sgpDrawFilledRects, _ARR _I32);
HL_PRIM void HL_NAME(sgpDrawFilledRect)(float x, float y, float w, float h) { sgp_draw_filled_rect(x, y, w, h); } DEFINE_PRIM(_VOID, sgpDrawFilledRect, _F32 _F32 _F32 _F32);
HL_PRIM void HL_NAME(sgpDrawTexturedRects)(const sgp_rect* rects, uint32_t count) { sgp_draw_textured_rects(*((sgp_rect**)(hl_aptr(rects, sgp_rect*))), count); } DEFINE_PRIM(_VOID, sgpDrawTexturedRects, _ARR _I32);
HL_PRIM void HL_NAME(sgpDrawTexturedRect)(float x, float y, float w, float h) { sgp_draw_textured_rect(x, y, w, h); } DEFINE_PRIM(_VOID, sgpDrawTexturedRect, _F32 _F32 _F32 _F32);
HL_PRIM void HL_NAME(sgpDrawTexturedRectsEx)(int channel, const sgp_textured_rect* rects, uint32_t count) { sgp_draw_textured_rects_ex(channel,*((sgp_textured_rect**)(hl_aptr(rects, sgp_textured_rect*))),count); } DEFINE_PRIM(_VOID, sgpDrawTexturedRectsEx, _I32 _ARR _I32);
HL_PRIM void HL_NAME(sgpDrawTexturedRectEx)(int channel, sgp_rect dest_rect, sgp_rect src_rect) { sgp_draw_textured_rect_ex(channel, dest_rect, src_rect); } DEFINE_PRIM(_VOID, sgpDrawTexturedRectEx, _I32 _STRUCT _STRUCT);

HL_PRIM sgp_state* HL_NAME(sgpQueryState)() { return sgp_query_state(); } DEFINE_PRIM(_ARR, sgpQueryState, _NO_ARG);
HL_PRIM sgp_desc HL_NAME(sgpQueryDesc)() { return sgp_query_desc(); } DEFINE_PRIM(_STRUCT, sgpQueryDesc, _NO_ARG);

/////////////////////////////////////////////////////////////////////////////////////

vclosure* cb_init;
vclosure* cb_frame;
vclosure* cb_cleanup;
vclosure* cb_event;

const sapp_event* last_event = {};
HL_PRIM const sapp_event* HL_NAME(sAppGetLastEvent)() { return last_event; } DEFINE_PRIM(_STRUCT, sAppGetLastEvent, _NO_ARG);
HL_PRIM float HL_NAME(sAppDpiScale)() { return sapp_dpi_scale(); } DEFINE_PRIM(_F32, sAppDpiScale, _NO_ARG);

void init(void) { hl_dyn_call(cb_init,NULL,0); }
void frame(void) { hl_dyn_call(cb_frame,NULL,0); }
void cleanup(void) { hl_dyn_call(cb_cleanup,NULL,0); }
void event(const sapp_event* ev) { last_event = ev; hl_dyn_call(cb_event,NULL, 0); }

sapp_desc sokol_main(int argc, char* argv[]) { return {}; }
HL_PRIM void HL_NAME(sgMain)(vclosure* init_cb, vclosure* frame_cb, vclosure* cleanup_cb, vclosure* event_cb, sapp_desc* desc)
{
    hl_add_root(desc);
    cb_init = init_cb;
    cb_frame = frame_cb;
    cb_cleanup = cleanup_cb;
    cb_event = event_cb;
    hl_add_root(cb_init);
    hl_add_root(cb_frame);
    hl_add_root(cb_cleanup);
    hl_add_root(cb_event);

    int argc_utf8 = 0;
    char** argv_utf8 = _sapp_win32_command_line_to_utf8_argv(GetCommandLineW(), &argc_utf8);

    desc->init_cb = init;
    desc->frame_cb = frame;
    desc->cleanup_cb = cleanup;
    desc->event_cb = event;
    _sapp_win32_run(desc);
    _sapp_free(argv_utf8);
}
DEFINE_PRIM(_VOID, sgMain, _FUN(_VOID, _NO_ARG) _FUN(_VOID, _NO_ARG) _FUN(_VOID, _NO_ARG) _FUN(_VOID, _NO_ARG) _STRUCT)

//static void input(const sapp_event* ev) {
//    switch (ev->type) {
//    case SAPP_EVENTTYPE_MOUSE_DOWN:
//        if (ev->mouse_button == SAPP_MOUSEBUTTON_LEFT) {
//            sapp_lock_mouse(true);
//        }
//        break;
//
//    case SAPP_EVENTTYPE_MOUSE_UP:
//        if (ev->mouse_button == SAPP_MOUSEBUTTON_LEFT) {
//            sapp_lock_mouse(false);
//        }
//        break;
//
//    case SAPP_EVENTTYPE_MOUSE_MOVE:
//        if (sapp_mouse_locked()) {
//            cam_orbit(&state.camera, ev->mouse_dx * 0.25f, ev->mouse_dy * 0.25f);
//        }
//        break;
//
//    default:
//        break;
//    }
//}

HL_PRIM void HL_NAME(sdtxSetup)()
{
    sdtx_desc_t sdtx = {};
    sdtx.fonts[FONT_KC853] = sdtx_font_kc853();
    sdtx.fonts[FONT_KC854] = sdtx_font_kc854();
    sdtx.fonts[FONT_Z1013] = sdtx_font_z1013();
    sdtx.fonts[FONT_CPC] = sdtx_font_cpc();
    sdtx.fonts[FONT_C64] = sdtx_font_c64();
    sdtx.fonts[FONT_ORIC] = sdtx_font_oric();
    sdtx_setup(&sdtx);

} DEFINE_PRIM(_VOID, sdtxSetup, _NO_ARG);

HL_PRIM void HL_NAME(sdtxShutdown)() { sdtx_shutdown(); } DEFINE_PRIM(_VOID, sdtxShutdown, _NO_ARG);
HL_PRIM void HL_NAME(sdtxCanvas)(float w, float h) { sdtx_canvas(w,h); } DEFINE_PRIM(_VOID, sdtxCanvas, _F32 _F32);
HL_PRIM void HL_NAME(sdtxOrigin)(float x, float y) { sdtx_origin(x,y); } DEFINE_PRIM(_VOID, sdtxOrigin, _F32 _F32);
HL_PRIM void HL_NAME(sdtxHome)() { sdtx_home(); } DEFINE_PRIM(_VOID, sdtxHome, _NO_ARG);
HL_PRIM void HL_NAME(sdtxFont)(int font_index) { sdtx_font(font_index); } DEFINE_PRIM(_VOID, sdtxFont, _I32);
HL_PRIM void HL_NAME(sdtxColor3b)(uint8_t r, uint8_t g, uint8_t b) { sdtx_color3b(r,g,b); } DEFINE_PRIM(_VOID, sdtxColor3b, _I32 _I32 _I32);
HL_PRIM void HL_NAME(sdtxPuts)(const char* str) { sdtx_puts(str); } DEFINE_PRIM(_VOID, sdtxPuts, _BYTES);
HL_PRIM void HL_NAME(sdtxPutc)(char chr) { sdtx_putc(chr); } DEFINE_PRIM(_VOID, sdtxPutc, _I32);
HL_PRIM void HL_NAME(sdtxCrlf)() { sdtx_crlf(); } DEFINE_PRIM(_VOID, sdtxCrlf, _NO_ARG);

static void print_font(int font_index, const char* title, uint8_t r, uint8_t g, uint8_t b) {
    sdtx_font(font_index);
    sdtx_color3b(r, g, b);
    sdtx_puts(title);
    for (int c = 32; c < 256; c++) {
        sdtx_putc(c);
        if (((c + 1) & 63) == 0) {
            sdtx_crlf();
        }
    }
    sdtx_crlf();
}

HL_PRIM void HL_NAME(sdtxTest)()
{
    // set virtual canvas size to half display size so that
    // glyphs are 16x16 display pixels
    sdtx_canvas(sapp_width() * 0.5f, sapp_height() * 0.5f);
    sdtx_origin(0.0f, 2.0f);
    sdtx_home();
    print_font(FONT_KC853, "KC85/3:\n", 0xf4, 0x43, 0x36);
    print_font(FONT_KC854, "KC85/4:\n", 0x21, 0x96, 0xf3);
    print_font(FONT_Z1013, "Z1013:\n", 0x4c, 0xaf, 0x50);
    print_font(FONT_CPC, "Amstrad CPC:\n", 0xff, 0xeb, 0x3b);
    print_font(FONT_C64, "C64:\n", 0x79, 0x86, 0xcb);
    print_font(FONT_ORIC, "Oric Atmos:\n", 0xff, 0x98, 0x00);

} DEFINE_PRIM(_VOID, sdtxTest, _NO_ARG);
HL_PRIM void HL_NAME(sdtxDraw)() { sdtx_draw(); } DEFINE_PRIM(_VOID, sdtxDraw, _NO_ARG);

HL_PRIM void HL_NAME(sglSetup)() { sgl_desc_t sglDesc = {}; sgl_setup(&sglDesc); } DEFINE_PRIM(_VOID, sglSetup, _NO_ARG);
HL_PRIM void HL_NAME(sglDraw)() { sgl_draw(); } DEFINE_PRIM(_VOID, sglDraw, _NO_ARG);
HL_PRIM void HL_NAME(sglShutdown)() { sgl_shutdown(); } DEFINE_PRIM(_VOID, sglShutdown, _NO_ARG);
HL_PRIM void HL_NAME(sglDefaults)() { sgl_defaults(); } DEFINE_PRIM(_VOID, sglDefaults, _NO_ARG);
HL_PRIM void HL_NAME(sglMatrixModeProjection)() { sgl_matrix_mode_projection(); } DEFINE_PRIM(_VOID, sglMatrixModeProjection, _NO_ARG);
HL_PRIM void HL_NAME(sglOrtho)(float l, float r, float b, float t, float n, float f) { sgl_ortho(l, r, b, t, n, f); } DEFINE_PRIM(_VOID, sglOrtho, _F32 _F32 _F32 _F32 _F32 _F32);

/*
typedef struct {
    FONScontext* fons;
    float dpi_scale;
    int font_normal;
    int font_italic;
    int font_bold;
    uint8_t font_normal_data[256 * 1024];
    uint8_t font_italic_data[256 * 1024];
    uint8_t font_bold_data[256 * 1024];
} state_t;
state_t state;

// optional memory allocation function overrides (see sfons_create())
void* my_alloc(size_t size, void* user_data) {
    (void)user_data;
    return malloc(size);
}

void my_free(void* ptr, void* user_data) {
    (void)user_data;
    free(ptr);
}

// sokol-fetch load callbacks
void font_normal_loaded(const sfetch_response_t* response) {
    if (response->fetched) {
        state.font_normal = fonsAddFontMem(state.fons, "sans", (unsigned char*)response->data.ptr, (int)response->data.size, false);
    }
}

void font_italic_loaded(const sfetch_response_t* response) {
    if (response->fetched) {
        state.font_italic = fonsAddFontMem(state.fons, "sans-italic", (unsigned char*)response->data.ptr, (int)response->data.size, false);
    }
}

void font_bold_loaded(const sfetch_response_t* response) {
    if (response->fetched) {
        state.font_bold = fonsAddFontMem(state.fons, "sans-bold", (unsigned char*)response->data.ptr, (int)response->data.size, false);
    }
}

HL_PRIM void HL_NAME(fsIinit)()
{
    state.dpi_scale = sapp_dpi_scale();

    // make sure the fontstash atlas width/height is pow-2
    const int atlas_dim = round_pow2(512.0f * state.dpi_scale);
    sfons_desc_t fons_desc = {
        .width = atlas_dim,
            .height = atlas_dim,
             allocator functions are optional, just check if it works
            .allocator = {
                .alloc = my_alloc,
                .free = my_free,
        }
    };
    FONScontext* fons_context = sfons_create(&fons_desc);
    state.fons = fons_context;
    state.font_normal = FONS_INVALID;
    state.font_italic = FONS_INVALID;
    state.font_bold = FONS_INVALID;

    // use sokol_fetch for loading the TTF font files
    sfetch_desc_t sfetchdesc  = { .num_channels = 1, .num_lanes = 4 };
    sfetch_setup(&sfetchdesc);

    char path_buf[512];
    sfetch_request_t req1 = {
        .path = fileutil_get_path("DroidSerif-Regular.ttf", path_buf, sizeof(path_buf)),
            .callback = font_normal_loaded,
            .buffer = SFETCH_RANGE(state.font_normal_data),
    };
    sfetch_send(&req1);
    sfetch_request_t req2 = {
        .path = fileutil_get_path("DroidSerif-Bold.ttf", path_buf, sizeof(path_buf)),
            .callback = font_bold_loaded,
            .buffer = SFETCH_RANGE(state.font_bold_data),
    };
    sfetch_send(&req2);
    sfetch_request_t req3 = {
        .path = fileutil_get_path("DroidSerif-Italic.ttf", path_buf, sizeof(path_buf)),
            .callback = font_italic_loaded,
            .buffer = SFETCH_RANGE(state.font_italic_data),
    };
    sfetch_send(&req3);

} DEFINE_PRIM(_VOID, fsIinit, _NO_ARG);


static void line(float sx, float sy, float ex, float ey)
{
    sgl_begin_lines();
    sgl_c4b(255, 255, 0, 128);
    sgl_v2f(sx, sy);
    sgl_v2f(ex, ey);
    sgl_end();
}

HL_PRIM void HL_NAME(fsTestFrame)()
{
    const float dpis = state.dpi_scale;

    // pump sokol_fetch message queues
    sfetch_dowork();

    // text rendering via fontstash.h 
    float sx, sy, dx, dy, lh = 0.0f;
    uint32_t white = sfons_rgba(255, 255, 255, 255);
    uint32_t black = sfons_rgba(0, 0, 0, 255);
    uint32_t brown = sfons_rgba(192, 128, 0, 128);
    uint32_t blue = sfons_rgba(0, 192, 255, 255);
    fonsClearState(state.fons);

    sgl_defaults();
    sgl_matrix_mode_projection();
    sgl_ortho(0.0f, sapp_widthf(), sapp_heightf(), 0.0f, -1.0f, +1.0f);

    sx = 50 * dpis; sy = 50 * dpis;
    dx = sx; dy = sy;

    FONScontext* fs = state.fons;
    if (state.font_normal != FONS_INVALID) {
        fonsSetFont(fs, state.font_normal);
        fonsSetSize(fs, 124.0f * dpis);
        fonsVertMetrics(fs, NULL, NULL, &lh);
        dx = sx;
        dy += lh;
        fonsSetColor(fs, white);
        dx = fonsDrawText(fs, dx, dy, "The quick ", NULL);
    }
    if (state.font_italic != FONS_INVALID) {
        fonsSetFont(fs, state.font_italic);
        fonsSetSize(fs, 48.0f * dpis);
        fonsSetColor(fs, brown);
        dx = fonsDrawText(fs, dx, dy, "brown ", NULL);
    }
    if (state.font_normal != FONS_INVALID) {
        fonsSetFont(fs, state.font_normal);
        fonsSetSize(fs, 24.0f * dpis);
        fonsSetColor(fs, white);
        dx = fonsDrawText(fs, dx, dy, "fox ", NULL);
    }
    if ((state.font_normal != FONS_INVALID) && (state.font_italic != FONS_INVALID) && (state.font_bold != FONS_INVALID)) {
        fonsVertMetrics(fs, NULL, NULL, &lh);
        dx = sx;
        dy += lh * 1.2f;
        fonsSetFont(fs, state.font_italic);
        dx = fonsDrawText(fs, dx, dy, "jumps over ", NULL);
        fonsSetFont(fs, state.font_bold);
        dx = fonsDrawText(fs, dx, dy, "the lazy ", NULL);
        fonsSetFont(fs, state.font_normal);
        dx = fonsDrawText(fs, dx, dy, "dog.", NULL);
    }
    if (state.font_normal != FONS_INVALID) {
        dx = sx;
        dy += lh * 1.2f;
        fonsSetSize(fs, 12.0f * dpis);
        fonsSetFont(fs, state.font_normal);
        fonsSetColor(fs, blue);
        fonsDrawText(fs, dx, dy, "Now is the time for all good men to come to the aid of the party.", NULL);
    }
    if (state.font_italic != FONS_INVALID) {
        fonsVertMetrics(fs, NULL, NULL, &lh);
        dx = sx;
        dy += lh * 1.2f * 2;
        fonsSetSize(fs, 18.0f * dpis);
        fonsSetFont(fs, state.font_italic);
        fonsSetColor(fs, white);
        fonsDrawText(fs, dx, dy, "Ég get etið gler án þess að meiða mig.", NULL);
    }

    // Font alignment
    if (state.font_normal != FONS_INVALID) {
        fonsSetSize(fs, 18.0f * dpis);
        fonsSetFont(fs, state.font_normal);
        fonsSetColor(fs, white);
        dx = 50 * dpis; dy = 350 * dpis;
        line(dx - 10 * dpis, dy, dx + 250 * dpis, dy);
        fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_TOP);
        dx = fonsDrawText(fs, dx, dy, "Top", NULL);
        dx += 10 * dpis;
        fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_MIDDLE);
        dx = fonsDrawText(fs, dx, dy, "Middle", NULL);
        dx += 10 * dpis;
        fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);
        dx = fonsDrawText(fs, dx, dy, "Baseline", NULL);
        dx += 10 * dpis;
        fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BOTTOM);
        fonsDrawText(fs, dx, dy, "Bottom", NULL);
        dx = 150 * dpis; dy = 400 * dpis;
        line(dx, dy - 30 * dpis, dx, dy + 80.0f * dpis);
        fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);
        fonsDrawText(fs, dx, dy, "Left", NULL);
        dy += 30 * dpis;
        fonsSetAlign(fs, FONS_ALIGN_CENTER | FONS_ALIGN_BASELINE);
        fonsDrawText(fs, dx, dy, "Center", NULL);
        dy += 30 * dpis;
        fonsSetAlign(fs, FONS_ALIGN_RIGHT | FONS_ALIGN_BASELINE);
        fonsDrawText(fs, dx, dy, "Right", NULL);
    }

    // Blur
    if (state.font_italic != FONS_INVALID) {
        dx = 500 * dpis; dy = 350 * dpis;
        fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);
        fonsSetSize(fs, 60.0f * dpis);
        fonsSetFont(fs, state.font_italic);
        fonsSetColor(fs, white);
        fonsSetSpacing(fs, 5.0f * dpis);
        fonsSetBlur(fs, 10.0f);
        fonsDrawText(fs, dx, dy, "Blurry...", NULL);
    }

    if (state.font_bold != FONS_INVALID) {
        dy += 50.0f * dpis;
        fonsSetSize(fs, 18.0f * dpis);
        fonsSetFont(fs, state.font_bold);
        fonsSetColor(fs, black);
        fonsSetSpacing(fs, 0.0f);
        fonsSetBlur(fs, 3.0f);
        fonsDrawText(fs, dx, dy + 2, "DROP THAT SHADOW", NULL);
        fonsSetColor(fs, white);
        fonsSetBlur(fs, 0);
        fonsDrawText(fs, dx, dy, "DROP THAT SHADOW", NULL);
    }

    // flush fontstash's font atlas to sokol-gfx texture
    sfons_flush(fs);

    // render pass
    sg_begin_default_pass(&(sg_pass_action) {
        .colors[0] = {
            .action = SG_ACTION_CLEAR, .value = { 0.3f, 0.3f, 0.32f, 1.0f }
        }
    }, sapp_width(), sapp_height());
} DEFINE_PRIM(_VOID, fsTestFrame, _NO_ARG);

HL_PRIM void HL_NAME(fsCleanUp)()
{
    sfetch_shutdown();
    sfons_destroy(state.fons);

} DEFINE_PRIM(_VOID, fsCleanUp, _NO_ARG);
*/

HL_PRIM FONScontext* HL_NAME(sFonsCreate)(sfons_desc_t* fons_desc) { return sfons_create(fons_desc);} DEFINE_PRIM(_STRUCT, sFonsCreate, _STRUCT);
HL_PRIM int HL_NAME(sFonsAddFontMem)(FONScontext* stash, const char* name, unsigned char* data, int dataSize, int freeData) { return fonsAddFontMem(stash,name,data,dataSize,freeData);} DEFINE_PRIM(_I32, sFonsAddFontMem, _STRUCT _BYTES _BYTES _I32 _BOOL);
HL_PRIM void HL_NAME(sFonsClearState)(FONScontext* stash) { fonsClearState(stash); } DEFINE_PRIM(_VOID, sFonsClearState, _STRUCT);
HL_PRIM void HL_NAME(sFonsSetFont)(FONScontext* stash, int font) { fonsSetFont(stash, font); } DEFINE_PRIM(_VOID, sFonsSetFont, _STRUCT _I32);
HL_PRIM void HL_NAME(sFonsSetSize)(FONScontext* stash, float size) { fonsSetSize(stash, size); } DEFINE_PRIM(_VOID, sFonsSetSize, _STRUCT _F32);
HL_PRIM void HL_NAME(sFonsVertMetrics)(FONScontext* stash, float* ascender, float* descender, float* lineh) { fonsVertMetrics(stash, ascender, descender, lineh); } DEFINE_PRIM(_VOID, sFonsVertMetrics, _STRUCT _F32 _F32 _F32);
HL_PRIM void HL_NAME(sFonsSetColor)(FONScontext* stash, unsigned int color) { fonsSetColor(stash,color); } DEFINE_PRIM(_VOID, sFonsSetColor, _STRUCT _I32);
HL_PRIM float HL_NAME(sFonsDrawText)(FONScontext* stash, float x, float y, const char* str, const char* end) { return fonsDrawText(stash,x,y,str,end);} DEFINE_PRIM(_F32, sFonsDrawText, _STRUCT _F32 _F32 _BYTES _BYTES);
HL_PRIM void HL_NAME(sFonsSetAlign)(FONScontext* stash, int align) { fonsSetAlign(stash, align); } DEFINE_PRIM(_VOID, sFonsSetAlign, _STRUCT _I32);
HL_PRIM void HL_NAME(sFonsSetSpacing)(FONScontext* stash, float spacing) { fonsSetSpacing(stash, spacing); } DEFINE_PRIM(_VOID, sFonsSetSpacing, _STRUCT _F32);
HL_PRIM void HL_NAME(sFonsSetBlur)(FONScontext* stash, float blur) { fonsSetBlur(stash, blur); } DEFINE_PRIM(_VOID, sFonsSetBlur, _STRUCT _F32);
HL_PRIM void HL_NAME(sFonsFlush)(FONScontext* stash) { sfons_flush(stash); } DEFINE_PRIM(_VOID, sFonsFlush, _STRUCT);
HL_PRIM void HL_NAME(sFonsDestroy)(FONScontext* stash) { sfons_destroy(stash); } DEFINE_PRIM(_VOID, sFonsDestroy, _STRUCT);
