package;

import Main.Test123;
import hl.NativeArray;

@:hlNative("hlSokol")
class D3d11
{
	/////////////////////////////////////////////////////////////////////////////////////

	@:hlNative("hlSokol","d3dInit")					static public function init(width:Int,height:Int,sampleCount:Int,title:HLString) {}
	@:hlNative("hlSokol","d3d11ProcessEvents")		static public function processEvents():Bool { return false; }
	@:hlNative("hlSokol","d3d11Width")				static public function width():Int { return 0; }
	@:hlNative("hlSokol","d3d11Height")				static public function height():Int { return 0; }
	@:hlNative("hlSokol","d3d11Present")			static public function present() {}
	@:hlNative("hlSokol","d3d11Shutdown")			static public function shutdown() {}

	/////////////////////////////////////////////////////////////////////////////////////
}

@:hlNative("hlSokol")
class Sg
{
	/////////////////////////////////////////////////////////////////////////////////////

	@:hlNative("hlSokol","sgSetup")					static public function setup() {}
	@:hlNative("hlSokol","sgBeginDefaultPass")		static public function beginDefaultPass(width:Int,height:Int) {}
	@:hlNative("hlSokol","sgEndPass")				static public function endPass() {}
	@:hlNative("hlSokol","sgCommit")				static public function commit() {}
	@:hlNative("hlSokol","sgShutdown")				static public function shutdown() {}
	@:hlNative("hlSokol","sgMakeBuffer")			static public function makeBuffer(vertices:HLArray<Single>):SgBuffer { return null;}
	@:hlNative("hlSokol","sgMakeShader")			static public function makeShader():SgShader { return null;}
	@:hlNative("hlSokol","sgMakePipeline")			static public function makePipeline(shader:SgShader):SgPipeline { return null;}
	@:hlNative("hlSokol","sgApplyPipeline")			static public function applyPipeline(pipeline:SgPipeline) {}
	@:hlNative("hlSokol","sgApplyBindings")			static public function applyBindings(bindings:SgBindings) {}
	@:hlNative("hlSokol","sgDraw")					static public function draw(baseElement:Int,numElements:Int,numInstances:Int) {}

	/////////////////////////////////////////////////////////////////////////////////////
}

@:hlNative("hlSokol")
class Sapp
{
	/////////////////////////////////////////////////////////////////////////////////////

	@:hlNative("hlSokol","sgMain")					static public function start(cbInit:Void->Void,cbFrame:Void->Void,cbCleanup:Void->Void,cbEvent:Void->Void,desc:SappDesc) {}
	@:hlNative("hlSokol","sAppWidth")				static public function width():Int { return 0; }
	@:hlNative("hlSokol","sAppHeight")				static public function height():Int { return 0; }
	@:hlNative("hlSokol","sAppGetLastEvent")		static public function getLastEvent():SappEvent { return null; }

	/////////////////////////////////////////////////////////////////////////////////////
}

@:hlNative("hlSokol")
class Sgp
{
	/////////////////////////////////////////////////////////////////////////////////////

	@:hlNative("hlSokol","test")					static public function test(send:Test123) {}
	@:hlNative("hlSokol","sgpSetup")				static public function setup() {}
	@:hlNative("hlSokol","sgpShutdown")				static public function shutdown() {}
	@:hlNative("hlSokol","sgpIsValid")				static public function isValid():Bool { return false; }

	@:hlNative("hlSokol","sgpGetLastError")			static public function getLastError():SgpError { return SgpError.SGP_NO_ERROR; }
	@:hlNative("hlSokol","sgpGetErrorMessage")		static public function getErrorMessage(error:SgpError):HLString { return null; }

	@:hlNative("hlSokol","sgpMakePipeline")			static public function makePipeline(desc:SgpPipelineDesc):SgPipeline { return null; }

	@:hlNative("hlSokol","sgpBegin")				static public function begin(width:Int,height:Int) {}
	@:hlNative("hlSokol","sgpFlush")				static public function flush() {}
	@:hlNative("hlSokol","sgpEnd")					static public function end() {}

	@:hlNative("hlSokol","sgpProject")				static public function project(left:Single,right:Single,top:Single,bottom:Single) {}
	@:hlNative("hlSokol","sgpResetProject")			static public function resetProject() {}

	@:hlNative("hlSokol","sgpPushTransform")		static public function pushTransform() {}
	@:hlNative("hlSokol","sgpPopTransform")			static public function popTransform() {}
	@:hlNative("hlSokol","sgpResetTransform")		static public function resetTransform() {}
	@:hlNative("hlSokol","sgpTranslate")			static public function translate(x:Single,y:Single) {}
	@:hlNative("hlSokol","sgpRotate")				static public function rotate(theta:Single) {}
	@:hlNative("hlSokol","sgpRotateAt")				static public function rotateAt(theta:Single,x:Single,y:Single) {}
	@:hlNative("hlSokol","sgpScale")				static public function scale(sx:Single,sy:Single) {}
	@:hlNative("hlSokol","sgpScaleAt")				static public function scaleAt(sx:Single,sy:Single,x:Single,y:Single) {}

	@:hlNative("hlSokol","sgpViewport")				static public function viewport(x:Int,y:Int,width:Int,height:Int) {}
	@:hlNative("hlSokol","sgpResetViewport")		static public function resetViewport() {}
	@:hlNative("hlSokol","sgpScissor")				static public function sgpScissor(x:Int,y:Int,width:Int,height:Int) {}
	@:hlNative("hlSokol","sgpResetScissor")			static public function resetScissor() {}
	@:hlNative("hlSokol","sgpResetState")			static public function resetState() {}

	@:hlNative("hlSokol","sgpSetPipeline")			static public function setPipeline(pipeline:SgPipeline) {}
	@:hlNative("hlSokol","sgpResetPipeline")		static public function resetPipeline() {}
	@:hlNative("hlSokol","sgpSetUniform")			static public function setUniform(data:hl.Bytes,size:Int) {}
	@:hlNative("hlSokol","sgpResetUniform")			static public function resetUniform() {}

	@:hlNative("hlSokol","sgpSetBlendMode")			static public function setBlendMode(blendMode:SgpBlendMode) {}
	@:hlNative("hlSokol","sgpResetBlendMode")		static public function resetBlendMode() {}
	@:hlNative("hlSokol","sgpSetColor")				static public function setColor(r:Float,g:Float,b:Float,a:Float) {}
	@:hlNative("hlSokol","sgpResetColor")			static public function resetColor() {}
	@:hlNative("hlSokol","sgpSetImage")				static public function setImage(channel:Int,image:SgImage) {}
	@:hlNative("hlSokol","sgpUnsetImage")			static public function unsetImage(channel:Int) {}
	@:hlNative("hlSokol","sgpResetImage")			static public function sgpResetImage(channel:Int) {}

	@:hlNative("hlSokol","sgpClear")				static public function clear() {}
	@:hlNative("hlSokol","sgpDrawPoints")			static public function drawPoints(points:HLArray<SgpPoint>,count:Int) {}
	@:hlNative("hlSokol","sgpDrawPoint")			static public function drawPoint(x:Single,y:Single) {}
	@:hlNative("hlSokol","sgpDrawLines")			static public function drawLines(lines:HLArray<SgpLine>,count:Int) {}
	@:hlNative("hlSokol","sgpDrawLine")				static public function drawLine(ax:Single,ay:Single,bx:Single,by:Single) {}
	@:hlNative("hlSokol","sgpDrawLinesStrip")		static public function drawLinesStrip(points:HLArray<SgpPoint>,count:Int) {}
	@:hlNative("hlSokol","sgpDrawFilledTriangles")	static public function drawFilledTriangles(triangles:HLArray<SgpTriangle>,count:Int) {}
	@:hlNative("hlSokol","sgpDrawFilledTriangle")	static public function drawFilledTriangle(ax:Single,ay:Single,bx:Single,by:Single,cx:Single,cy:Single) {}
	@:hlNative("hlSokol","sgpDrawFilledTrianglesStrip") static public function drawFilledTrianglesStrip(points:HLArray<SgpPoint>,count:Int) {}
	@:hlNative("hlSokol","sgpDrawFilledRects")		static public function drawFilledRects(rects:HLArray<SgpRect>,count:Int) {}
	@:hlNative("hlSokol","sgpDrawFilledRect")		static public function drawFilledRect(x:Single,y:Single,width:Single,height:Single) {}
	@:hlNative("hlSokol","sgpDrawTexturedRects")	static public function drawTexturedRects(rects:HLArray<SgpRect>,count:Int) {}
	@:hlNative("hlSokol","sgpDrawTexturedRectsEx")	static public function drawTexturedRectsEx(channel:Int, rects:HLArray<SgpTexturedRect>,count:Int) {}
	@:hlNative("hlSokol","sgpDrawTexturedRectEx")	static public function drawTexturedRectEx(channel:Int, dest_rect:SgpRect,src_rect:SgpRect) {}

	@:hlNative("hlSokol","sgpQueryState")			static public function queryState():HLArray<SgpState> { return null; }
	@:hlNative("hlSokol","sgpQueryDesc")			static public function queryDesc():SgpDesc { return null; }

	/////////////////////////////////////////////////////////////////////////////////////
}

@:hlNative("hlSokol")
class Sdtx
{
	/////////////////////////////////////////////////////////////////////////////////////

	@:hlNative("hlSokol","sdtxSetup")				static public function setup() {}
	@:hlNative("hlSokol","sdtxShutdown")			static public function shutdown() {}
	@:hlNative("hlSokol","sdtxTest")				static public function test() {}
	@:hlNative("hlSokol","sdtxCanvas")				static public function canvas(w:Single,h:Single) {}
	@:hlNative("hlSokol","sdtxOrigin")				static public function origin(x:Single,y:Single) {}
	@:hlNative("hlSokol","sdtxHome")				static public function home() {}
	@:hlNative("hlSokol","sdtxFont")				static public function font(fontIndex:Int) {}
	@:hlNative("hlSokol","sdtxColor3b")				static public function color3b(r:Int,g:Int,b:Int) {}
	@:hlNative("hlSokol","sdtxPuts")				static public function puts(str:HLString) {}
	@:hlNative("hlSokol","sdtxPutc")				static public function putc(chr:Int) {}
	@:hlNative("hlSokol","sdtxCrlf")				static public function crlf() {}
	@:hlNative("hlSokol","sdtxDraw")				static public function draw() {}

	/////////////////////////////////////////////////////////////////////////////////////
}

abstract HLString(hl.Bytes)
{
  	inline function new(b:hl.Bytes)
	{
    	this = b;
  	}

   	@:from
  	static public function fromString(s:String)
	{
		if (s==null)
			return null;
		return new HLString(@:privateAccess s.toUtf8());
  	}	

  	@:to
  	public function toString():String
	{
		return @:privateAccess String.fromUTF8(this);
  	}	
}

@:forward(length)
abstract HLArray<T>(hl.NativeArray<T>)
{
  	inline function new(arr:hl.NativeArray<T>)
	{
    	this = arr;
  	}

   	@:from
  	static inline public function fromArray<T>(a:Array<T>)
	{
		if (a==null)
			return null;
		final na = new hl.NativeArray<T>(a.length);
		var i = 0;
		for (e in a)
		{
			na[i]=a[i];
			i++;
		}
		return new HLArray(na);
  	}	

   	@:from
  	static public function alloc<T>(length:Int)
	{
		return new HLArray(new hl.NativeArray<T>(length));
  	}	

  	@:to
  	public function toArray():Array<T>
	{
		var a:Array<T> = [];
		for (e in this)
			a.push(e);
		return a;
  	}	

	@:arrayAccess
	public inline function get(index:Int):T
	{
		return this[index];
	}
	
	@:arrayAccess
	public inline function set(index:Int,value:T):T
	{
		this[index]=value;
		return value;
	}	
}

@:publicFields @:struct @:keep @:structInit class SgBuffer { var id:Int; }
@:publicFields @:struct @:keep @:structInit class SgImage { var id:Int; }
@:publicFields @:struct @:keep @:structInit class SgShader { var id:Int; }
@:publicFields @:struct @:keep @:structInit class SgPipeline { var id:Int; }
@:publicFields @:struct @:keep @:structInit class SgPass { var id:Int; }
@:publicFields @:struct @:keep @:structInit class SgContext { var id:Int; }

@:publicFields @:struct @:keep @:structInit class SgpDesc
{
	var max_vertices:Int;
	var max_commands:Int;
}

@:publicFields @:struct @:keep @:structInit class SgpState
{
	var frame_size:hl.Abstract<"sgp_isize">;
	var viewport:hl.Abstract<"sgp_irect">;
	var scissor:hl.Abstract<"sgp_irect">;
	var proj:hl.Abstract<"sgp_mat2x3">;
	var transform:hl.Abstract<"sgp_mat2x3">;
	var mvp:hl.Abstract<"sgp_mat2x3">;
	var color:hl.Abstract<"sgp_color">;
	var images:hl.Abstract<"sgp_images_uniform">;
	var uniform:hl.Abstract<"sgp_uniform">;
	var blend_mode:hl.Abstract<"sgp_blend_mode">;
	var pipeline:hl.Abstract<"sg_pipeline">;
	var _base_vertex:Int;
	var _base_uniform:Int;
	var _base_command:Int;
}

@:publicFields @:struct @:keep @:structInit class SgpPipelineDesc
{
	var shader:hl.Abstract<"sg_shader_desc">;
	var primitive_type:hl.Abstract<"sg_primitive_type">;
	var blend_mode:SgpBlendMode;
}

@:publicFields @:struct @:keep @:structInit class SgpRect
{
	var x:Single;
	var y:Single;
	var w:Single;
	var h:Single;
}

@:publicFields @:struct @:keep @:structInit class SgpPoint
{
	public function new(x:Single,y:Single)
	{
		this.x = x;
		this.y = y;
	}
	var x:Single;
	var y:Single;

	public static inline function create(x:Single,y:Single):SgpPoint
		return new SgpPoint(x,y);
}
typedef SgpVec2 = SgpPoint;

@:publicFields @:struct @:keep @:structInit class SgpLine
{
	public inline function new(ax:Single,ay:Single,bx:Single,by:Single)
	{
		this.a = ({x:ax,y:ay}:SgpPoint);
		this.b = ({x:bx,y:by}:SgpPoint);
	}
	var a:SgpPoint;
	var b:SgpPoint;

	public static inline function create(ax:Single,ay:Single,bx:Single,by:Single):SgpLine
		return new SgpLine(ax,ay,bx,by);
}

@:publicFields @:struct @:keep @:structInit class SgpTriangle
{
	public inline function new(ax:Single,ay:Single,bx:Single,by:Single,cx:Single,cy:Single)
	{
		this.a = ({x:ax,y:ay}:SgpPoint);
		this.b = ({x:bx,y:by}:SgpPoint);
		this.c = ({x:cx,y:cy}:SgpPoint);
	}
	var a:SgpPoint;
	var b:SgpPoint;
	var c:SgpPoint;

	public static inline function create(ax:Single,ay:Single,bx:Single,by:Single,cx:Single,cy:Single):SgpTriangle
		return new SgpTriangle(ax,ay,bx,by,cx,cy);
}

@:publicFields @:struct @:keep @:structInit class SgpTexturedRect
{
	public inline function new(dstx:Single,dsty:Single,dstw:Single,desth:Single,srcx:Single,srcy:Single,srcw:Single,srch:Single)
	{
		this.dst = ({x:dstx,y:dsty,w:dstw,h:desth}:SgpRect);
		this.src = ({x:srcx,y:srcy,w:srcw,h:srch}:SgpRect);
	}
	var dst:SgpRect;
	var src:SgpRect;

	public static inline function create(dstx:Single,dsty:Single,dstw:Single,desth:Single,srcx:Single,srcy:Single,srcw:Single,srch:Single):SgpTexturedRect
		return new SgpTexturedRect(dstx,dsty,dstw,desth,srcx,srcy,srcw,srch);
}

@:publicFields @:struct @:keep @:structInit class SgBindings
{
	@:optional var _start_canary			: Int;
	@:optional var vertex_buffers			: HLArray<SgBuffer> = HLArray.alloc(8);
	@:optional var vertex_buffer_offsets	: HLArray<Int> = HLArray.alloc(8);
	@:optional var index_buffer				: SgBuffer;
	@:optional var index_buffer_offset		: Int;
	@:optional var vs_images				: HLArray<SgImage> = HLArray.alloc(12);
	@:optional var fs_images				: HLArray<SgImage> = HLArray.alloc(12);
	@:optional var _end_canary				: Int;
}

@:publicFields @:struct @:keep @:structInit class SappDesc
{
	public inline function new(title:String="HlSokol",width:Int=1280,height:Int=720,sampleCount:Int=4,fullscreen:Bool=false,highDpi:Bool=false)
	{
		this.window_title = title;
		this.width = width;
		this.height = height;
		this.sample_count = sampleCount;
		this.fullscreen = fullscreen;
		this.high_dpi = highDpi;
	}

	var init_cb							: hl.Abstract<"void (*init_cb)(void)">;
	var frame_cb						: hl.Abstract<"void (*frame_cb)(void)">;
	var cleanup_cb						: hl.Abstract<"void (*cleanup_cb)(void)">;
	var event_cb						: hl.Abstract<"void (*event_cb)(const sapp_event*)">;
	var fail_cb							: hl.Abstract<"void (*fail_cb)(const char*)">;
	var user_data						: hl.Abstract<"void*">;
	var init_userdata_cb				: hl.Abstract<"void (*init_userdata_cb)(void*)">;
	var frame_userdata_cb				: hl.Abstract<"void (*frame_userdata_cb)(void*)">;
	var cleanup_userdata_cb				: hl.Abstract<"void (*cleanup_userdata_cb)(void*)">;
	var event_userdata_cb				: hl.Abstract<"void (*event_userdata_cb)(const sapp_event*, void*)">;
	var fail_userdata_cb				: hl.Abstract<"void (*fail_userdata_cb)(const char*, void*)">;

	var width							: Int;
	var height							: Int;
	var sample_count					: Int;
	var swap_interval					: Int;
	var high_dpi						: Bool;
	var fullscreen						: Bool;
	var alpha							: Bool;
	var window_title					: HLString;
	var enable_clipboard				: Bool;
	var clipboard_size					: Int;
	var enable_dragndrop				: Bool;
	var max_dropped_files				: Int;
	var max_dropped_file_path_length 	: Int;
	var icon						 	: hl.Abstract<"sapp_icon_desc">;
	var allocator					 	: hl.Abstract<"sapp_allocator">;
	var logger						 	: hl.Abstract<"sapp_logger"> ;
	var gl_force_gles2 					: Bool;
	var gl_major_version				: Int;
	var gl_minor_version				: Int;
	var win32_console_utf8				: Bool;
	var win32_console_create			: Bool;
	var win32_console_attach			: Bool;
	var html5_canvas_name				: HLString;
	var html5_canvas_resize				: Bool;
	var html5_preserve_drawing_buffer	: Bool;
	var html5_premultiplied_alpha 		: Bool;
	var html5_ask_leave_site			: Bool;
	var ios_keyboard_resizes_canvas		: Bool;
}

@:publicFields @:struct @:keep @:structInit class SappEvent
{
	@:optional var frame_count				: hl.I64;				// current frame counter, always valid, useful for checking if two events were issued in the same frame
	@:optional var type						: SappEventType;	// the event type, always valid
	@:optional var key_code					: SappKeycode;		// the virtual key code, only valid in KEY_UP, KEY_DOWN
	@:optional var char_code				: Int;				// the UTF-32 character code, only valid in CHAR events
	@:optional var key_repeat				: Bool;				// true if this is a key-repeat event, valid in KEY_UP, KEY_DOWN and CHAR
	@:optional var modifiers				: Int;				// current modifier keys, valid in all key-, char- and mouse-events
	@:optional var mouse_button				: SappMouseButton;	// mouse button that was pressed or released, valid in MOUSE_DOWN, MOUSE_UP
	@:optional var mouse_x					: Single;			// current horizontal mouse position in pixels, always valid except during mouse lock	
	@:optional var mouse_y					: Single;			// current vertical mouse position in pixels, always valid except during mouse lock
	@:optional var mouse_dx					: Single;			// relative horizontal mouse movement since last frame, always valid
	@:optional var mouse_dy					: Single;			// relative vertical mouse movement since last frame, always valid
	@:optional var scroll_x					: Single;			// horizontal mouse wheel scroll distance, valid in MOUSE_SCROLL events
	@:optional var scroll_y					: Single;			// vertical mouse wheel scroll distance, valid in MOUSE_SCROLL events
	@:optional var int						: Int;				// number of valid items in the touches[] array
	@:optional var touches					: HLArray<StouchPoint> = HLArray.alloc(10); // current touch points, valid in TOUCHES_BEGIN, TOUCHES_MOVED, TOUCHES_ENDED
	@:optional var window_width				: Int;				// current window- and framebuffer sizes in pixels, always valid
	@:optional var window_height			: Int;
	@:optional var framebuffer_width		: Int;				// = window_width * dpi_scale
	@:optional var framebuffer_height		: Int;				// = window_height * dpi_scale
}

@:publicFields @:struct @:keep @:structInit class StouchPoint
{
	@:optional var frame_count				: Int;
	@:optional var pos_x					: Single;
	@:optional var pos_y					: Single;
	@:optional var android_tooltype			: hl.Abstract<"sapp_android_tooltype">; // only valid on Android
	@:optional var changed					: Bool;
}

enum abstract SgpBlendMode(Int)
{
    var SGP_BLENDMODE_NONE=0; 	  /* No blending. dstRGBA = srcRGBA */
    var SGP_BLENDMODE_BLEND=1;    /* Alpha blending. dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA)); dstA = srcA + (dstA * (1-srcA)) */
    var SGP_BLENDMODE_ADD=2;      /* Color add. dstRGB = (srcRGB * srcA) + dstRGB; dstA = dstA */
    var SGP_BLENDMODE_MOD=3;      /* Color modulate. dstRGB = srcRGB * dstRGB; dstA = dstA */
    var SGP_BLENDMODE_MUL=4;      /* Color multiply. dstRGB = (srcRGB * dstRGB) + (dstRGB * (1-srcA)); dstA = (srcA * dstA) + (dstA * (1-srcA)) */
}

enum abstract SgpError(Int)
{
    var SGP_NO_ERROR = 1;
    var SGP_ERROR_SOKOL_INVALID = 2;
    var SGP_ERROR_VERTICES_FULL = 3;
    var SGP_ERROR_UNIFORMS_FULL = 4;
    var SGP_ERROR_COMMANDS_FULL = 5;
    var SGP_ERROR_VERTICES_OVERFLOW = 6;
    var SGP_ERROR_TRANSFORM_STACK_OVERFLOW = 7;
    var SGP_ERROR_TRANSFORM_STACK_UNDERFLOW = 8;
    var SGP_ERROR_STATE_STACK_OVERFLOW = 9;
    var SGP_ERROR_STATE_STACK_UNDERFLOW = 10;
    var SGP_ERROR_ALLOC_FAILED = 11;
    var SGP_ERROR_MAKE_VERTEX_BUFFER_FAILED = 12;
    var SGP_ERROR_MAKE_WHITE_IMAGE_FAILED = 13;
    var SGP_ERROR_MAKE_COMMON_SHADER_FAILED = 14;
    var SGP_ERROR_MAKE_COMMON_PIPELINE_FAILED = 15;
}

enum abstract SappEventType(Int)
{
    var SAPP_EVENTTYPE_INVALID = 0;
    var SAPP_EVENTTYPE_KEY_DOWN = 1;
    var SAPP_EVENTTYPE_KEY_UP = 2;
    var SAPP_EVENTTYPE_CHAR = 3;
    var SAPP_EVENTTYPE_MOUSE_DOWN = 4;
    var SAPP_EVENTTYPE_MOUSE_UP = 5;
    var SAPP_EVENTTYPE_MOUSE_SCROLL = 6;
    var SAPP_EVENTTYPE_MOUSE_MOVE = 7;
    var SAPP_EVENTTYPE_MOUSE_ENTER = 8;
    var SAPP_EVENTTYPE_MOUSE_LEAVE = 9;
    var SAPP_EVENTTYPE_TOUCHES_BEGAN = 10;
    var SAPP_EVENTTYPE_TOUCHES_MOVED = 11;
    var SAPP_EVENTTYPE_TOUCHES_ENDED = 12;
    var SAPP_EVENTTYPE_TOUCHES_CANCELLED = 13;
    var SAPP_EVENTTYPE_RESIZED = 14;
    var SAPP_EVENTTYPE_ICONIFIED = 15;
    var SAPP_EVENTTYPE_RESTORED = 16;
    var SAPP_EVENTTYPE_FOCUSED = 17;
    var SAPP_EVENTTYPE_UNFOCUSED = 18;
    var SAPP_EVENTTYPE_SUSPENDED = 19;
    var SAPP_EVENTTYPE_RESUMED = 20;
    var SAPP_EVENTTYPE_QUIT_REQUESTED = 21;
    var SAPP_EVENTTYPE_CLIPBOARD_PASTED = 22;
    var SAPP_EVENTTYPE_FILES_DROPPED = 23;
}

enum abstract SappMouseButton(Int)
{
    var SAPP_EVENTTYPE_INVALID = 0;
    var SAPP_MOUSEBUTTON_LEFT = 0x0;
    var SAPP_MOUSEBUTTON_RIGHT = 0x1;
    var SAPP_MOUSEBUTTON_MIDDLE = 0x2;
    var SAPP_MOUSEBUTTON_INVALID = 0x100;
}

enum abstract SappKeycode(Int)
{
    var SAPP_KEYCODE_INVALID          = 0;
    var SAPP_KEYCODE_SPACE            = 32;
    var SAPP_KEYCODE_APOSTROPHE       = 39;  /* ' */
    var SAPP_KEYCODE_COMMA            = 44;  /* , */
    var SAPP_KEYCODE_MINUS            = 45;  /* - */
    var SAPP_KEYCODE_PERIOD           = 46;  /* . */
    var SAPP_KEYCODE_SLASH            = 47;  /* / */
    var SAPP_KEYCODE_0                = 48;
    var SAPP_KEYCODE_1                = 49;
    var SAPP_KEYCODE_2                = 50;
    var SAPP_KEYCODE_3                = 51;
    var SAPP_KEYCODE_4                = 52;
    var SAPP_KEYCODE_5                = 53;
    var SAPP_KEYCODE_6                = 54;
    var SAPP_KEYCODE_7                = 55;
    var SAPP_KEYCODE_8                = 56;
    var SAPP_KEYCODE_9                = 57;
    var SAPP_KEYCODE_SEMICOLON        = 59;  /* ; */
    var SAPP_KEYCODE_EQUAL            = 61;  /* = */
    var SAPP_KEYCODE_A                = 65;
    var SAPP_KEYCODE_B                = 66;
    var SAPP_KEYCODE_C                = 67;
    var SAPP_KEYCODE_D                = 68;
    var SAPP_KEYCODE_E                = 69;
    var SAPP_KEYCODE_F                = 70;
    var SAPP_KEYCODE_G                = 71;
    var SAPP_KEYCODE_H                = 72;
    var SAPP_KEYCODE_I                = 73;
    var SAPP_KEYCODE_J                = 74;
    var SAPP_KEYCODE_K                = 75;
    var SAPP_KEYCODE_L                = 76;
    var SAPP_KEYCODE_M                = 77;
    var SAPP_KEYCODE_N                = 78;
    var SAPP_KEYCODE_O                = 79;
    var SAPP_KEYCODE_P                = 80;
    var SAPP_KEYCODE_Q                = 81;
    var SAPP_KEYCODE_R                = 82;
    var SAPP_KEYCODE_S                = 83;
    var SAPP_KEYCODE_T                = 84;
    var SAPP_KEYCODE_U                = 85;
    var SAPP_KEYCODE_V                = 86;
    var SAPP_KEYCODE_W                = 87;
    var SAPP_KEYCODE_X                = 88;
    var SAPP_KEYCODE_Y                = 89;
    var SAPP_KEYCODE_Z                = 90;
    var SAPP_KEYCODE_LEFT_BRACKET     = 91;  /* [ */
    var SAPP_KEYCODE_BACKSLASH        = 92;  /* \ */
    var SAPP_KEYCODE_RIGHT_BRACKET    = 93;  /* ] */
    var SAPP_KEYCODE_GRAVE_ACCENT     = 96;  /* ` */
    var SAPP_KEYCODE_WORLD_1          = 161; /* non-US #1 */
    var SAPP_KEYCODE_WORLD_2          = 162; /* non-US #2 */
    var SAPP_KEYCODE_ESCAPE           = 256;
    var SAPP_KEYCODE_ENTER            = 257;
    var SAPP_KEYCODE_TAB              = 258;
    var SAPP_KEYCODE_BACKSPACE        = 259;
    var SAPP_KEYCODE_INSERT           = 260;
    var SAPP_KEYCODE_DELETE           = 261;
    var SAPP_KEYCODE_RIGHT            = 262;
    var SAPP_KEYCODE_LEFT             = 263;
    var SAPP_KEYCODE_DOWN             = 264;
    var SAPP_KEYCODE_UP               = 265;
    var SAPP_KEYCODE_PAGE_UP          = 266;
    var SAPP_KEYCODE_PAGE_DOWN        = 267;
    var SAPP_KEYCODE_HOME             = 268;
    var SAPP_KEYCODE_END              = 269;
    var SAPP_KEYCODE_CAPS_LOCK        = 280;
    var SAPP_KEYCODE_SCROLL_LOCK      = 281;
    var SAPP_KEYCODE_NUM_LOCK         = 282;
    var SAPP_KEYCODE_PRINT_SCREEN     = 283;
    var SAPP_KEYCODE_PAUSE            = 284;
    var SAPP_KEYCODE_F1               = 290;
    var SAPP_KEYCODE_F2               = 291;
    var SAPP_KEYCODE_F3               = 292;
    var SAPP_KEYCODE_F4               = 293;
    var SAPP_KEYCODE_F5               = 294;
    var SAPP_KEYCODE_F6               = 295;
    var SAPP_KEYCODE_F7               = 296;
    var SAPP_KEYCODE_F8               = 297;
    var SAPP_KEYCODE_F9               = 298;
    var SAPP_KEYCODE_F10              = 299;
    var SAPP_KEYCODE_F11              = 300;
    var SAPP_KEYCODE_F12              = 301;
    var SAPP_KEYCODE_F13              = 302;
    var SAPP_KEYCODE_F14              = 303;
    var SAPP_KEYCODE_F15              = 304;
    var SAPP_KEYCODE_F16              = 305;
    var SAPP_KEYCODE_F17              = 306;
    var SAPP_KEYCODE_F18              = 307;
    var SAPP_KEYCODE_F19              = 308;
    var SAPP_KEYCODE_F20              = 309;
    var SAPP_KEYCODE_F21              = 310;
    var SAPP_KEYCODE_F22              = 311;
    var SAPP_KEYCODE_F23              = 312;
    var SAPP_KEYCODE_F24              = 313;
    var SAPP_KEYCODE_F25              = 314;
    var SAPP_KEYCODE_KP_0             = 320;
    var SAPP_KEYCODE_KP_1             = 321;
    var SAPP_KEYCODE_KP_2             = 322;
    var SAPP_KEYCODE_KP_3             = 323;
    var SAPP_KEYCODE_KP_4             = 324;
    var SAPP_KEYCODE_KP_5             = 325;
    var SAPP_KEYCODE_KP_6             = 326;
    var SAPP_KEYCODE_KP_7             = 327;
    var SAPP_KEYCODE_KP_8             = 328;
    var SAPP_KEYCODE_KP_9             = 329;
    var SAPP_KEYCODE_KP_DECIMAL       = 330;
    var SAPP_KEYCODE_KP_DIVIDE        = 331;
    var SAPP_KEYCODE_KP_MULTIPLY      = 332;
    var SAPP_KEYCODE_KP_SUBTRACT      = 333;
    var SAPP_KEYCODE_KP_ADD           = 334;
    var SAPP_KEYCODE_KP_ENTER         = 335;
    var SAPP_KEYCODE_KP_EQUAL         = 336;
    var SAPP_KEYCODE_LEFT_SHIFT       = 340;
    var SAPP_KEYCODE_LEFT_CONTROL     = 341;
    var SAPP_KEYCODE_LEFT_ALT         = 342;
    var SAPP_KEYCODE_LEFT_SUPER       = 343;
    var SAPP_KEYCODE_RIGHT_SHIFT      = 344;
    var SAPP_KEYCODE_RIGHT_CONTROL    = 345;
    var SAPP_KEYCODE_RIGHT_ALT        = 346;
    var SAPP_KEYCODE_RIGHT_SUPER      = 347;
    var SAPP_KEYCODE_MENU             = 348;
}

