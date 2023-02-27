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
#include "sokol_gp.h"
#include "sokol_app.h"
#include "sokol_glue.h"

//#define _SG_BUFFER _ABSTRACT(sg_buffer)
//#define _SG_BINDINGS _ABSTRACT(sg_bindings*)
//#define _SG_ERROR _ABSTRACT(sgp_error)
//#define _SG_BLENDMODE _ABSTRACT(sgp_blend_mode)
//#define _SG_PIPELINE _ABSTRACT(sg_pipeline)
//#define _SG_PIPELINE_DESC _ABSTRACT(sgp_pipeline_desc)
//#define _SG_IMAGE _ABSTRACT(sg_image)
//#define _SG_POINTS _ABSTRACT(sgp_point*)
//#define _SG_LINES _ABSTRACT(sgp_line*)
//#define _SG_TRIANGLES _ABSTRACT(sgp_triangle*)
//#define _SG_RECT _ABSTRACT(sgp_rect)
//#define _SG_RECTS _ABSTRACT(sgp_rect*)
//#define _SG_TEXTURED_RECTS _ABSTRACT(sgp_textured_rect*)
//#define _SGP_STATE _ABSTRACT(sgp_state*)
//#define _SGP_DESC _ABSTRACT(sgp_desc)
//#define _DEVICEINFO _OBJ(_BYTES _BYTES)

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
HL_PRIM void HL_NAME(sgApplyBindings)(const sg_bindings* bind) { sg_apply_bindings(bind); } DEFINE_PRIM(_VOID, sgApplyBindings, _STRUCT);
HL_PRIM void HL_NAME(sgDraw)(int base_element, int num_elements, int num_instances) { sg_draw(base_element, num_elements, num_instances); } DEFINE_PRIM(_VOID, sgDraw, _I32 _I32 _I32);

HL_PRIM void HL_NAME(d3d11Present)() { d3d11_present(); } DEFINE_PRIM(_VOID, d3d11Present, _NO_ARG);
HL_PRIM void HL_NAME(sgShutdown)() { sg_shutdown(); } DEFINE_PRIM(_VOID, sgShutdown, _NO_ARG);
HL_PRIM void HL_NAME(d3d11Shutdown)() { d3d11_shutdown(); } DEFINE_PRIM(_VOID, d3d11Shutdown, _NO_ARG);
HL_PRIM int HL_NAME(d3d11Width)() { return d3d11_width(); } DEFINE_PRIM(_I32, d3d11Width, _NO_ARG);
HL_PRIM int HL_NAME(d3d11Height)() { return d3d11_height(); } DEFINE_PRIM(_I32, d3d11Height, _NO_ARG);


HL_PRIM int HL_NAME(sAppWidth)() { return sapp_width(); } DEFINE_PRIM(_I32, sAppWidth, _NO_ARG);
HL_PRIM int HL_NAME(sAppHeight)() { return sapp_height(); } DEFINE_PRIM(_I32, sAppHeight, _NO_ARG);


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

void init(void) { hl_dyn_call(cb_init,NULL,0); }
void frame(void) { hl_dyn_call(cb_frame,NULL,0); }
void cleanup(void) { hl_dyn_call(cb_cleanup,NULL,0); }

sapp_desc sokol_main(int argc, char* argv[]) { return {}; }
HL_PRIM void HL_NAME(sgMain)(vclosure* init_cb, vclosure* frame_cb, vclosure* cleanup_cb, sapp_desc* desc)
{
    hl_add_root(desc);
    cb_init = init_cb;
    cb_frame = frame_cb;
    cb_cleanup = cleanup_cb;
    hl_add_root(cb_init);
    hl_add_root(cb_frame);
    hl_add_root(cb_cleanup);

    int argc_utf8 = 0;
    char** argv_utf8 = _sapp_win32_command_line_to_utf8_argv(GetCommandLineW(), &argc_utf8);

    desc->init_cb = init;
    desc->frame_cb = frame;
    desc->cleanup_cb = cleanup;
    _sapp_win32_run(desc);
    _sapp_free(argv_utf8);
}
DEFINE_PRIM(_VOID, sgMain, _FUN(_VOID, _NO_ARG) _FUN(_VOID, _NO_ARG) _FUN(_VOID, _NO_ARG) _STRUCT)
