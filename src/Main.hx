package;

import Sokol.SgPipeline;
import Sokol.SgBindings;
import Sokol.SAppDesc;
import Sokol.HLString;
import Sokol.SgpRect;
import Sokol.SgpLine;
import Sokol.SgpPoint;
import Sokol.SApp;
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
		var desc:SAppDesc = new SAppDesc("What the window...!",1400,800,4,false);
		SApp.start(init,frame,shutdown,desc);
	}

	static public function init()
	{
		Sg.setup();
		Sgp.setup();
		if (!Sgp.isValid())
		{
			var err = Sgp.getLastError();
			var errMsg = "Failed to create Sokol GP context: "+ Sgp.getErrorMessage(err);
			trace(errMsg);
			Sys.exit(1);
		}
		var vertices:Array<Single> = 
		[
			/* positions            colors */
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
		pip = Sg.makePipeline(shd);
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
		lns = HLArray.alloc(20000);
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
		var w = SApp.width();
		var h = SApp.height();
		var ratio = w/h;

		Sgp.begin(w,h);
		Sgp.viewport(0,0,w,h);
		Sgp.project(0,w,0,h);
		// Sgp.translate(-ratio,1);
		// Sgp.scale(1/w,1/h);

		Sgp.setColor(0.1,0.1,0.1,1.0);
		Sgp.clear();
		
		Sgp.setBlendMode(SGP_BLENDMODE_BLEND);

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

		// var pts:HLArray<SgpPoint> = HLArray.alloc(5000);
		// for (i in 0...pts.length)
			// pts[i]=({x:Math.random()*100,y:Math.random()*100}:SgpPoint);
		// Sgp.drawPoints(pts,pts.length);

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
		Sgp.flush();
		Sgp.end();
		
		Sg.endPass();
		Sg.commit();

		rot+=1;
	}

	static function shutdown()
	{
		Sgp.shutdown();
		Sg.shutdown();
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