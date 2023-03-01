package;

import Sokol.Sgl;
import Sokol.Sfs;
import Sokol.SappMouseButton;
import Sokol.SappKeycode;
import Sokol.SappEventType;
import Sokol.SappEvent;
import Sokol.SgPipeline;
import Sokol.SgBindings;
import Sokol.SappDesc;
import Sokol.HLString;
import Sokol.SgpRect;
import Sokol.SgpLine;
import Sokol.SgpPoint;
import Sokol.Sapp;
import Sokol.Sdtx;
import Sokol.HLArray;
import Sokol.Sg;
import Sokol.Sgp;
import Sokol.D3d11;
import Sokol.HLString;
import hl.Ref;
import hl.NativeArray;
import haxe.Timer;
import Sokol.Sg;

class Main
{
	static public function main()
	{
		var desc:SappDesc = new SappDesc("What the window...!",1400,800,4,false);
		desc.high_dpi = true;
		desc.gl_force_gles2 = true;
		Sapp.start(init,frame,shutdown,event,desc);
	}

	static public function init()
	{
		Sg.setup();
		Sgl.setup();
 		Sgp.setup();
		Sfs.init();
		Sdtx.setup();
		
		if (!Sgp.isValid())
		{
			var err = Sgp.getLastError();
			var errMsg = "Failed to create Sokol GP context: "+ Sgp.getErrorMessage(err);
			trace(errMsg);
			Sys.exit(1);
		}
/*		var vertices:Array<Single> = 
		[
			//positions            colors
			0.0, 0.5, 0.5,      1.0, 0.0, 0.0, 1.0,
			0.5, -0.5, 0.5,     0.0, 1.0, 0.0, 1.0,
			-0.5, -0.5, 0.5,    0.0, 0.0, 1.0, 1.0
		];

		// var na:NativeArray<Float> = new NativeArray<Float>(vertices.length);
		// for (i in 0...vertices.length)
		// 	na[i]=vertices[i];
		var vbuf = Sg.makeBuffer(vertices);
		bind.vertex_buffers[0]=vbuf;
		var shd = Sg.makeShader();
		pip = Sg.makePipeline(shd); */
	// 	  sg_bindings bind = {
    //     .vertex_buffers[0] = vbuf
    // };
		// Sg.sgMakeBindings(buf);
		// mainEvent = MainLoop.add(update);

		// var h2:HLArray<Single> = vertices;

		// // trace(h2);

		// var t123 = new Test123();
		// t123.myFloat = 0.33;
		// t123.myInt = 127;
		// t123.myStr = "Halla balla";
		// // t123.vals = HLArray.fromArray(vertices);
		// t123.vals = vertices;
		// t123.vals = HLArray.alloc(4);
		// t123.vals[0]=0.3;
		// t123.vals[1]=0.5;
		// t123.vals[2]=0.7;
		// t123.vals[3]=0.9;
		// t123.vals = vertices;

		// t123.valz=["Hey","you","fish!"];
		// t123.doh = new TPoint(45.3,77.8);
		// Sgp.test(t123);

		// var desc = Sgp.queryDesc();
		// trace(t123.valz);
		// var nm=5000;
		// for (i in 0...nm)
		// 	pts[i]=({x:Math.random()*2-1,y:Math.random()*2-1}:SgpPoint);
		// lns = HLArray.alloc(20000);
		// for (i in 0...400)
		// {
		// 	lns[i]=({ax:Math.random()*1920,ay:Math.random()*1080,bx:Math.random()*1920,by:Math.random()*1080}:SgpLine);
		// 	// Sgp.drawLine(lns[i].a.x,lns[i].a.y,lns[i].b.x,lns[i].b.y);
		// }
	}

	static var bind:SgBindings = {};
	static var pip:SgPipeline;

	static var rot : Single = 0.0;
	static var lns:HLArray<SgpLine> = HLArray.alloc(20000);
	static var pts:HLArray<SgpPoint> = HLArray.alloc(5000);
	static var rts:HLArray<SgpRect> = HLArray.alloc(10);

	public static function frame()
	{
		var w = Sapp.width();
		var h = Sapp.height();
		var ratio = w/h;
		Sg.beginDefaultPass(w,h);

/* 		Sg.applyPipeline(pip);
		Sg.applyBindings(bind);
		Sg.beginDefaultPass(w,h);
		Sg.draw(0,3,1);
 */
		// Sdtx.test();



	 	Sgp.begin(w,h);
		Sgp.viewport(0,0,w,h);
		Sgp.project(0,w,0,h);
		// Sgp.translate(-ratio,1);
		// Sgp.scale(1/w,1/h);
		Sgp.setBlendMode(SGP_BLENDMODE_BLEND);

		Sgp.setColor(0.1,0.1,0.1,1.0);
		Sgp.clear();
		Sgp.setColor(0,1,0,1.0);
		for (y in 0...100)
			for (x in 0...100)
				Sgp.drawPoint(x*10,y*10);

		Sgp.setColor((Math.sin(rot*0.1)*0.5)+0.5,0.4,0,0.4);
		Sgp.pushTransform();
		Sgp.rotateAt(rot*(Math.PI/180),400,400);
		Sgp.drawFilledRect(300,300,400,300);

		Sgp.popTransform();
		Sgp.setColor(1,1,1,1);

		final e:SappEvent = Sapp.getLastEvent();
		if (e!=null)
		{
			var i = 0;
			var cir = ShapePoints.circle2(mouseDown?e.mouse_x:300,mouseDown?e.mouse_y:300,(Math.sin(Timer.stamp())*100)+150);
			while (i<cir.length-2)
			{
				Sgp.drawLine(cir[i],cir[i+1],cir[i+2],cir[i+3]);
				i+=2;
			}
		}
		Sgp.flush();


		Sdtx.canvas(w*0.5,h*0.5);
		Sdtx.origin(4,4);
		Sdtx.home();
		Sdtx.font(5);
		Sdtx.color3b(0x22, 0xff, 0x33);
		Sdtx.puts('Whats up : ${Math.random()}');
		Sdtx.crlf();
		Sdtx.font(1);
		Sdtx.color3b(0xff, 0x22, 0x33);
		Sdtx.puts("Thats cool...");
		Sdtx.crlf();
		Sdtx.draw();

/*


		// Sgp.setColor((Math.sin(rot*0.1)*0.5)+0.5,0.4,0,0.4);
		// Sgp.rotateAt(rot*(Math.PI/180),0,0);
		// Sgp.drawFilledRect(-0.5,-0.5,1,1);

		Sgp.setColor(0,1,0,0.99);

		Sg.beginDefaultPass(w,h);
		Sg.applyPipeline(pip);
		Sg.applyBindings(bind);
		Sg.draw(0,3,1);

		// Sgp.drawLine(-0.5,0.0,0.5,0.5);

		// for (y in 0...100)
		// 	for (x in 0...100)
		// 		Sgp.drawPoint(x*10,y*10);

		// Sgp.drawLinesStrip(pts,5000);

		// Sgp.setColor(1,1,1,0.25);
		// for (i in 0...rts.length)
		// 	rts[i]=({x:Math.random()*w,y:Math.random()*h,w:100,h:100}:SgpRect);

		// Sgp.drawFilledRects(rts,rts.length);

		// Sgp.setColor(0,1,0,0.025);
		// for (i in 0...lns.length)
		// {
		// 	lns[i]=({ax:Math.random()*w,ay:Math.random()*h,bx:Math.random()*w,by:Math.random()*h}:SgpLine);
		// 	Sgp.drawLine(lns[i].a.x,lns[i].a.y,lns[i].b.x,lns[i].b.y);
		// }
		// for (i in 0...400)
		// {
		// 	lns[i]=({ax:Math.random()*w,ay:Math.random()*h,bx:Math.random()*w,by:Math.random()*h}:SgpLine);
		// 	Sgp.drawLine(lns[i].a.x,lns[i].a.y,lns[i].b.x,lns[i].b.y);
		// }
		// Sgp.drawLines(lns,400);

		// Sg.beginDefaultPass(w,h);
*/		
		Sfs.testFrame();
		Sgl.draw();
		
		Sgp.end();
		Sg.endPass();
		Sg.commit();

		rot+=1;
	}

	static function shutdown()
	{
		Sdtx.shutdown();
		Sgp.shutdown();
		Sfs.cleanUp();
		Sgl.shutdown();
		Sg.shutdown();
	}

	static var mouseDown:Bool = false;

	static function event()
	{
		final e:SappEvent = Sapp.getLastEvent();
		if (e.type == SappEventType.SAPP_EVENTTYPE_KEY_DOWN && e.key_code==SappKeycode.SAPP_KEYCODE_F)
			Sapp.toggleFullscreen();
		
		if (e.mouse_button!=SappMouseButton.SAPP_MOUSEBUTTON_INVALID)
			mouseDown=!mouseDown;
	}
}

/////////////////////////////////////////////////////////////////////////////////////	

@:publicFields @:struct @:keep class TPoint
{
	public inline function new(x:Float,y:Float)
	{
		this.x = x;
		this.y = y;
	}
	@:optional var x:Float;
	@:optional var y:Single;
}

@:publicFields @:struct @:structInit @:keep class Test123
{
	public inline function new()
	{

	}

	var myStr	: HLString;
	var myInt	: Int;
	var myFloat	: Single;
	var vals	: HLArray<Single>;
	var valz	: HLArray<HLString>;
	var doh		: TPoint;
}




class ShapePoints
{

	public static function circle2(cx: Float, cy: Float, radius: Float, segments: Int = 0):Array<Float>
	{
		// radius += strength / 2;

		if (segments <= 0)
			segments = Math.floor(10 * Math.sqrt(radius));

		var theta = 2 * Math.PI / segments;
		var c = Math.cos(theta);
		var s = Math.sin(theta);

		var x = radius;
		var y = 0.0;

		var cp:Array<Float> = [];
		for (n in 0...segments)
		{
			// var px = x + cx;
			// var py = y + cy;

			var t = x;
			x = c * x - s * y;
			y = c * y + s * t;
			cp.push(x+cx);
			cp.push(y+cy);
		}
		cp.push(cp[0]);
		cp.push(cp[1]);
		return cp;
	}

}