// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Dashboard HTML (PROGMEM)
//  Maximum Overdrive - Final Layout Fix (Adaptive Fluid UI)
// ═══════════════════════════════════════════════════════════════════

#ifndef MEDIPULSE_DASHBOARD_H
#define MEDIPULSE_DASHBOARD_H

#include <Arduino.h>

// ─────────────────────────────────────────────────────────────────
//  CHUNK 1 — <!DOCTYPE> + <head> + CSS
// ─────────────────────────────────────────────────────────────────

static const char HTML_CHUNK_CSS[] PROGMEM = R"rawhtml(<!DOCTYPE html><html lang="en"><head>
<meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>MediPulse Deep Core</title>
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;700;900&family=Share+Tech+Mono&display=swap" rel="stylesheet">
<script src="https://cdnjs.cloudflare.com/ajax/libs/gsap/3.12.2/gsap.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/three@0.128.0/examples/js/controls/OrbitControls.js"></script>
<script src="https://cdn.jsdelivr.net/npm/chart.js@4.4.0/dist/chart.umd.min.js"></script>

<style>
:root{--hud-c:#00e5ff; --hud-r:0,229,255; --bg:#02050a; --tx-w:#fff; --tx-d:#7388a1; --f-hdr:'Inter',sans-serif; --f-sci:'Share Tech Mono',monospace;}
*{box-sizing:border-box;margin:0;padding:0;}
body{background:var(--bg);color:var(--tx-w);font-family:var(--f-hdr);height:100vh;overflow:hidden;-webkit-font-smoothing:antialiased;user-select:none;}

/* MATRIX BACKGROUND */
.bg-mat{position:fixed;inset:0;background-image:linear-gradient(rgba(var(--hud-r),0.04) 1px,transparent 1px),linear-gradient(90deg,rgba(var(--hud-r),0.04) 1px,transparent 1px);background-size:40px 40px;background-position:center;z-index:1;pointer-events:none;}
.bg-vign{position:fixed;inset:0;background:radial-gradient(circle at center,transparent 20%,rgba(2,5,10,0.95) 100%);z-index:2;pointer-events:none;}
#ov{position:fixed;inset:0;background:transparent;z-index:9000;pointer-events:none;}

/* PAGE MANAGER */
.page{position:absolute;inset:0;display:none;opacity:0;z-index:10;flex-direction:column;align-items:center;justify-content:center;}

#p-boot{background:#000;z-index:99;font-family:var(--f-sci);color:var(--hud-c);font-size:1.4rem;text-shadow:0 0 15px var(--hud-c);}
#b-lg{min-height:200px;display:flex;flex-direction:column;gap:20px;letter-spacing:1px;}
.bt-trk{width:700px;height:4px;background:rgba(255,255,255,0.1);border-radius:2px;}
#b-br{height:100%;width:0;background:var(--hud-c);box-shadow:0 0 30px var(--hud-c);}
#p-logo{z-index:80;}
.lg-tit{font-size:9rem;font-weight:900;letter-spacing:-4px;color:#fff;text-shadow:0 0 80px rgba(0,229,255,0.4);margin:0;line-height:0.9;text-align:center;}
.lg-sub{font-size:1.6rem;font-family:var(--f-sci);color:var(--hud-c);letter-spacing:12px;margin-top:15px;text-align:center;}

#p-story{justify-content:flex-start;overflow-y:auto;z-index:70;} #p-story::-webkit-scrollbar{width:0;}
.st-wr{padding:80px 40px;max-width:1000px;margin:0 auto;display:flex;flex-direction:column;gap:100px;position:relative;}
.st-cd{display:flex;gap:40px;}
.st-ic{flex:0 0 auto;width:70px;height:70px;border:2px solid var(--hud-c);border-radius:50%;display:flex;align-items:center;justify-content:center;color:var(--hud-c);box-shadow:0 0 20px rgba(var(--hud-r),0.2);font-family:var(--f-sci);font-size:1.5rem;}
.st-bx{flex:1;} .st-bx h2{font-size:2.5rem;color:var(--hud-c);margin-bottom:20px;font-weight:900;letter-spacing:-1px;} .st-bx p{font-size:1.3rem;line-height:1.7;color:#fff;}
.btn-f{position:fixed;bottom:50px;right:50px;background:var(--hud-c);color:#000;padding:25px 50px;border-radius:50px;font-family:var(--f-sci);font-weight:900;font-size:1.2rem;letter-spacing:2px;border:none;cursor:pointer;z-index:100;box-shadow:0 0 40px rgba(var(--hud-r),0.4);transition:0.3s;}
.btn-f:hover{transform:scale(1.05);background:#fff;}

/* HUD RESPONSIVE LAYOUT */
#p-dash{display:block;}

.fs-btn{position:absolute;top:30px;right:30px;border:2px solid var(--hud-c);color:var(--hud-c);font-family:var(--f-sci);letter-spacing:2px;padding:12px 20px;cursor:pointer;z-index:100;background:rgba(0,0,0,0.5);transition:0.3s;box-shadow:inset 0 0 10px rgba(var(--hud-r),0.1);}
.fs-btn:hover{background:var(--hud-c);color:#000;box-shadow:0 0 20px var(--hud-c);}

/* FIXED SCIFI PANELS ZONES */
.t-pnl{position:absolute;top:25px;left:50%;transform:translateX(-50%);text-align:center;width:600px;display:flex;flex-direction:column;align-items:center;gap:10px;z-index:20;}
.bdg{font-family:var(--f-sci);font-size:1.6rem;color:var(--hud-c);letter-spacing:4px;border:1px solid var(--hud-c);padding:10px 50px;background:rgba(var(--hud-r),0.15);clip-path:polygon(15px 0,100% 0,calc(100% - 15px) 100%,0 100%);text-shadow:0 0 15px var(--hud-c);}
.tit-d{font-size:1.2rem;font-weight:900;letter-spacing:8px;color:#fff;text-shadow:0 0 10px rgba(255,255,255,0.3);}

/* Dynamic side stretch to fill empty screen width cleanly */
.l-pnl{position:absolute;top:100px;bottom:30px;left:40px;width:380px;display:flex;flex-direction:column;gap:30px;z-index:20;}
.r-pnl{position:absolute;top:100px;bottom:30px;right:40px;width:380px;display:flex;flex-direction:column;gap:30px;z-index:20;}
.b-pnl{position:absolute!important;top:130px;left:450px;right:450px;height:145px;z-index:20;}

/* SCIFI CARDS */
.sci-p{background:rgba(4,10,20,0.65);backdrop-filter:blur(8px);-webkit-backdrop-filter:blur(8px);border:1px solid rgba(255,255,255,0.05);border-top:2px solid var(--hud-c);clip-path:polygon(20px 0,100% 0,100% calc(100% - 20px),calc(100% - 20px) 100%,0 100%,0 20px);padding:25px;position:relative;display:flex;flex-direction:column;}
.sci-p::before{content:'';position:absolute;top:0;left:20px;width:50px;height:3px;background:var(--tx-w);z-index:2;}
.sci-p::after{content:'';position:absolute;inset:0;box-shadow:inset 0 0 35px rgba(var(--hud-r),0.15);pointer-events:none;}
.sci-h{font-family:var(--f-sci);font-size:1.05rem;letter-spacing:5px;color:var(--hud-c);margin-bottom:20px;z-index:2;}

/* EXACT CENTER 3D CORE */
.c-wrap{position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);width:500px;height:500px;display:flex;justify-content:center;align-items:center;z-index:10;pointer-events:none;}
#three-c{position:absolute;inset:0;display:flex;justify-content:center;align-items:center;z-index:5;}
.c-dat{position:absolute;text-align:center;pointer-events:none;z-index:15;display:flex;flex-direction:column;align-items:center;}
#h-val{font-size:8rem;font-weight:900;line-height:0.9;color:#fff;text-shadow:0 0 50px rgba(var(--hud-r),0.9);margin-bottom:5px;font-family:var(--f-sci);}
.c-lb{font-family:var(--f-sci);font-size:1.3rem;color:var(--hud-c);letter-spacing:8px;background:rgba(0,0,0,0.5);padding:5px 20px;border-radius:20px;}
.c-rg{position:absolute;border-radius:50%;border:2px solid transparent;pointer-events:none;}
.r1{inset:40px;border-left-color:var(--hud-c);border-right-color:var(--hud-c);animation:sp 15s linear infinite;opacity:0.4;}
.r2{inset:65px;border-top-color:var(--hud-c);border-bottom-color:var(--hud-c);animation:sp 10s linear infinite reverse;border-width:1px;opacity:0.2;}
@keyframes sp{to{transform:rotate(360deg)}}

/* PANELS INTERNALS */
.eq-w{display:flex;align-items:flex-end;gap:5px;height:75px;} .eq-b{flex:1;background:var(--hud-c);opacity:0.8;min-height:4px;}
.lgs{flex:1;overflow-y:auto;padding-right:15px;display:flex;flex-direction:column;gap:12px;min-height:0;}
.lgs::-webkit-scrollbar{width:4px;} .lgs::-webkit-scrollbar-thumb{background:var(--hud-c);}
.li{display:flex;justify-content:space-between;align-items:center;font-family:var(--f-sci);font-size:1.05rem;padding:12px 0;border-bottom:1px solid rgba(255,255,255,0.05);}
.li-tm{color:var(--tx-d);} .li-ty{color:var(--hud-c);}
.st-g{display:grid;grid-template-columns:1fr 1fr;grid-template-rows:1fr 1fr;gap:20px;flex:1;align-items:center;} .st-b{display:flex;flex-direction:column;gap:5px;}
.st-n{font-size:2.2rem;font-weight:700;color:#fff;font-family:var(--f-sci);} .st-l{font-family:var(--f-sci);color:var(--tx-d);letter-spacing:2px;}
</style></head>)rawhtml";

// ─────────────────────────────────────────────────────────────────
//  CHUNK 2 — Phase 1, 2, 3 (Boot, Logo, Story)
// ─────────────────────────────────────────────────────────────────

static const char HTML_CHUNK_PAGES[] PROGMEM = R"rawhtml(<body>
<div class="bg-mat"></div><div class="bg-vign"></div><div id="ov"></div>

<!-- BOOT -->
<div id="p-boot" class="page active" style="opacity:1;display:flex;">
  <div>
    <div id="b-lg"></div>
    <div class="bt-trk"><div id="b-br"></div></div>
  </div>
</div>

<!-- LOGO -->
<div id="p-logo" class="page">
  <div class="l-cont">
    <h1 class="lg-tit">MEDIPULSE</h1>
    <div class="lg-sub">AEROSPACE UI ONLINE</div>
  </div>
</div>

<!-- STORY -->
<div id="p-story" class="page">
  <button class="btn-f" onclick="goDash()">ENGAGE PROTOCOL</button>
  <div class="st-wr">
    <div class="st-cd i-obs"><div class="st-ic">01</div><div class="st-bx"><h2>HARDWARE CORE</h2><p>Running on advanced dual-core ESP32 topology. Telemetry is natively processed offline ensuring zero-latency vital evaluation.</p></div></div>
    <div class="st-cd i-obs"><div class="st-ic">02</div><div class="st-bx"><h2>ALGORITHM ENGINE</h2><p>Fourier-based physiological transforms continuously analyze biological and environmental matrices. Threat isolation is instantaneous.</p></div></div>
    <div class="st-cd i-obs"><div class="st-ic">03</div><div class="st-bx"><h2>3D DEFORMATION</h2><p>Raw heart telemetry feeds directly into WebGL physics. The 3D holographic sphere mathematically stretches and deforms with the real heartbeat data.</p></div></div>
    <div class="st-cd i-obs"><div class="st-ic">04</div><div class="st-bx"><h2>WEB AUDIO SYNTH</h2><p>Utilizing a fully procedural web audio synthesizer. Threat protocols generate mathematically calculated Klaxon siren waves instantly without external audio files.</p></div></div>
  </div>
</div>)rawhtml";

// ─────────────────────────────────────────────────────────────────
//  CHUNK 3 — Phase 4 (Dashboard HUD)
// ─────────────────────────────────────────────────────────────────

static const char HTML_CHUNK_DASH[] PROGMEM = R"rawhtml(<div id="p-dash" class="page">
  
  <div id="three-c"></div>

  <div class="fs-btn" onclick="tFS()">[ FULLSCREEN ]</div>
  
  <div class="t-pnl">
    <div class="tit-d">DEEP CORE // BIOMETRIC LINK</div>
    <div class="bdg" id="s-bdg">SYSTEM NORMAL</div>
  </div>

  <div class="l-pnl">
    <div class="sci-p" style="flex:0 0 auto">
      <h3 class="sci-h">ACOUSTIC RADAR</h3>
      <h1 id="s-txt" style="font-size:3.5rem;font-weight:900;font-family:var(--f-sci)">SILENT</h1>
      <div class="eq-w" id="eqz"></div>
    </div>
    <div class="sci-p" style="flex:1;min-height:0">
      <h3 class="sci-h">EVENT LOG DATABASE</h3>
      <div class="lgs" id="lgs" style="height:100%;"></div>
    </div>
  </div>

  <div class="r-pnl">
    <div class="sci-p" style="height:280px;flex:0 0 auto">
      <h3 class="sci-h">WAVEFORM TELEMETRY</h3>
      <div style="flex:1;min-height:0;margin-top:10px;"><canvas id="cht"></canvas></div>
    </div>
    <div class="sci-p" style="flex:1;min-height:0">
      <h3 class="sci-h">SYSTEM DIAGNOSTICS</h3>
      <div class="st-g">
        <div class="st-b"><div class="st-n" id="u-t">--</div><span class="st-l">UPTIME</span></div>
        <div class="st-b"><div class="st-n" id="u-r">--</div><span class="st-l">READS</span></div>
        <div class="st-b"><div class="st-n" id="u-h">--</div><span class="st-l">HEAP(KB)</span></div>
        <div class="st-b"><div class="st-n" id="u-a">--</div><span class="st-l">ALERTS</span></div>
      </div>
    </div>
  </div>

  <div class="b-pnl sci-p">
    <h3 class="sci-h" style="position:absolute;top:20px;left:25px;margin:0;">ECG LIVE SCAN</h3>
    <div style="width:100%;height:100%;padding-top:20px;"><canvas style="width:100%;height:100%" id="ecg"></canvas></div>
  </div>

  <div class="c-wrap" id="cr-wp">
    <div class="c-rg r1"></div><div class="c-rg r2"></div>
    
    <div class="c-dat">
      <div id="h-val">---</div>
      <div class="c-lb">PULSE RATE</div>
    </div>
  </div>

</div>)rawhtml";

// ─────────────────────────────────────────────────────────────────
//  CHUNK 4 — JS Engine (Web Audio, GSAP, ThreeJS, Scrambling)
// ─────────────────────────────────────────────────────────────────

static const char HTML_CHUNK_JS[] PROGMEM = R"rawhtml(<script>
function tFS(){if(!document.fullscreenElement)document.documentElement.requestFullscreen();else document.exitFullscreen();}

/* WEB AUDIO SYNTHESIZER */
const ACTX=new (window.AudioContext||window.webkitAudioContext)();
let s_osc=null, s_lfo=null, s_gn=null;
function pSr(){
  if(s_osc) return; if(ACTX.state==='suspended')ACTX.resume();
  s_osc=ACTX.createOscillator(); s_osc.type='sawtooth';
  s_lfo=ACTX.createOscillator(); s_lfo.type='sine'; s_lfo.frequency.setValueAtTime(2,ACTX.currentTime);
  let lG=ACTX.createGain(); lG.gain.setValueAtTime(400,ACTX.currentTime);
  s_osc.frequency.setValueAtTime(600,ACTX.currentTime); s_lfo.connect(lG); lG.connect(s_osc.frequency);
  s_gn=ACTX.createGain(); s_gn.gain.setValueAtTime(0.01,ACTX.currentTime); s_gn.gain.exponentialRampToValueAtTime(0.4,ACTX.currentTime+0.5);
  s_osc.connect(s_gn); s_gn.connect(ACTX.destination); s_lfo.start(); s_osc.start();
}
function sSr(){if(s_osc){s_gn.gain.exponentialRampToValueAtTime(0.0001,ACTX.currentTime+0.5);setTimeout(()=>{if(s_osc){s_osc.stop();s_lfo.stop();s_osc.disconnect();s_lfo.disconnect();s_osc=null;}},600);}}
const synth=window.speechSynthesis; function spk(t,r=1.05){try{if(synth&&!synth.speaking){let u=new SpeechSynthesisUtterance(t);u.rate=r;synth.speak(u);}}catch(e){}}

/* TEXT SCRAMBLE */
const cSet="!<>\\/[]{}—=+*^?#_01";
function scrmbl(el,v,dur=400){
  let t=String(v), i=0, it=dur/30, l=t.length;
  let inv=setInterval(()=>{
    let s=""; for(let j=0;j<l;j++) s+=(Math.random()<0.2)?t[j]:cSet[Math.floor(Math.random()*cSet.length)];
    el.innerText=s; i++; if(i>it){clearInterval(inv);el.innerText=t;}
  },30);
}

/* BOOT FLOW */
const pages={b:document.getElementById('p-boot'),l:document.getElementById('p-logo'),s:document.getElementById('p-story'),d:document.getElementById('p-dash')};
const bl=["[SYS] BOOTING NEURAL ENG.","[SYS] MOUNTING SENSORS...","[OK] ACQUISITION ONLINE","[OK] WEBGL THREE.JS ACTIVE","[OK] PROCEDURAL AUDIO SYNTH.","[OK] GSAP VIBRATION ARMED","> INITIATING MEDIPULSE HUD..."];
let bi=0;
function dBt(){
  if(bi<bl.length){ let d=document.createElement('div');d.innerHTML=bl[bi];document.getElementById('b-lg').appendChild(d); gsap.fromTo(d,{opacity:0,x:-20},{opacity:1,x:0,duration:0.3,ease:"power2.out"}); bi++;setTimeout(dBt, 200+Math.random()*300); }
  else {
    gsap.to('#b-br',{width:'100%',duration:1.5,ease:"expo.inOut",onComplete:()=>{
      spk("Initializing Core Subsystems"); gsap.to(pages.b,{autoAlpha:0,duration:1,onComplete:()=>{pages.b.style.display='none'}}); gsap.fromTo(pages.l,{autoAlpha:0,scale:0.95},{autoAlpha:1,scale:1,duration:1.5,display:'flex',ease:"expo.out"});
      gsap.to('.l-cont',{y:-15,repeat:-1,yoyo:true,duration:2.5,ease:"sine.inOut"});
      setTimeout(()=>{spk("Welcome to Aerospace UI");setTimeout(()=>{gsap.to(pages.l,{autoAlpha:0,duration:1,onComplete:()=>{pages.l.style.display='none'}});gsap.fromTo(pages.s,{autoAlpha:0,y:50},{autoAlpha:1,y:0,duration:1.5,display:'flex',ease:"back.out(1)",clearProps:"transform"});},3000);},1000);
    }});
  }
} setTimeout(dBt,800);

const obs=new IntersectionObserver((e)=>{e.forEach(ent=>{if(ent.isIntersecting&&!ent.target.dataset.a){ent.target.dataset.a="t";gsap.fromTo(ent.target,{opacity:0,y:40},{opacity:1,y:0,duration:1,ease:"back.out(1.5)"});}});},{threshold:0.1});
document.querySelectorAll('.i-obs').forEach(x=>obs.observe(x));

let dA=false;
function goDash(){
  if(ACTX.state==='suspended')ACTX.resume();
  spk("Engaging Biometric HUD"); gsap.to(pages.s,{autoAlpha:0,duration:0.6,y:-40,onComplete:()=>{pages.s.style.display='none'}});
  gsap.fromTo(pages.d,{autoAlpha:0,scale:1.05},{autoAlpha:1,scale:1,duration:1.5,display:'block',delay:0.5,ease:"expo.out"});
  gsap.fromTo('.sci-p',{opacity:0,y:50},{opacity:1,y:0,duration:1,stagger:0.1,delay:0.6,ease:"back.out(1)"});
  if(!dA){ dA=true; try{init3D();}catch(e){console.log("3D error",e);} pd(); ps(); pl(); }
}

/* PURE THREE.JS VERTEX ENGINE WITH ORBITCONTROLS */
let s3=null, c3=null, r3=null, sph=null, iSph=null, ctrl=null, bPos=null;
function init3D() {
  const c=document.getElementById('three-c'); s3=new THREE.Scene(); 
  c3=new THREE.PerspectiveCamera(60,window.innerWidth/window.innerHeight,0.1,1000);
  r3=new THREE.WebGLRenderer({alpha:true,antialias:true}); 
  r3.setSize(window.innerWidth,window.innerHeight); 
  c.appendChild(r3.domElement);
  
  if(typeof THREE.OrbitControls !== 'undefined') {
     ctrl=new THREE.OrbitControls(c3, r3.domElement); ctrl.enableDamping=true; ctrl.enablePan=false; ctrl.enableZoom=true; ctrl.minDistance=3; ctrl.maxDistance=30;
  }
  
  window.addEventListener('resize',()=>{
    if(c3 && r3){
      c3.aspect=window.innerWidth/window.innerHeight;
      c3.updateProjectionMatrix();
      r3.setSize(window.innerWidth,window.innerHeight);
    }
  });
  
  const g=new THREE.IcosahedronGeometry(2.3,1);
  const m=new THREE.MeshBasicMaterial({color:0x00e5ff,wireframe:true,transparent:true,opacity:0.4});
  sph=new THREE.Mesh(g,m); s3.add(sph);
  bPos=[]; const pa=sph.geometry.attributes.position.array; for(let i=0;i<pa.length;i++)bPos.push(pa[i]);
  
  const g2=new THREE.IcosahedronGeometry(1.6,0); const m2=new THREE.MeshBasicMaterial({color:0x00e5ff,wireframe:true,transparent:true,opacity:0.15});
  iSph=new THREE.Mesh(g2,m2); sph.add(iSph);
  
  c3.position.z=10; a3D();
}
function a3D() {
  requestAnimationFrame(a3D);
  if(sph){
    sph.rotation.x+=0.003; sph.rotation.y+=0.006; iSph.rotation.x-=0.01;
    const pa=sph.geometry.attributes.position.array;
    let tm=Date.now()*0.001*(cv>700?4:1); let thInt=(cv<250||cv>800)?0.3:0.04;
    for(let i=0;i<pa.length;i+=3){
      let bx=bPos[i], by=bPos[i+1], bz=bPos[i+2], len=Math.sqrt(bx*bx+by*by+bz*bz); if(len===0)continue;
      let ns=Math.sin(bx*2+tm)*Math.cos(by*2+tm)*Math.sin(bz*2+tm);
      let nL=len+ns*thInt; pa[i]=(bx/len)*nL; pa[i+1]=(by/len)*nL; pa[i+2]=(bz/len)*nL;
    }
    sph.geometry.attributes.position.needsUpdate=true;
  }
  if(ctrl) ctrl.update();
  r3.render(s3,c3);
}

/* EQ & ECG ENGINE */
const eq=document.getElementById('eqz'), eB=[]; for(let i=0;i<18;i++){let b=document.createElement('div');b.className='eq-b';eq.appendChild(b);eB.push(b);}
let snd=false; setInterval(()=>{eB.forEach(b=>{gsap.to(b,{height:snd?(15+Math.random()*60)+'px':(4+Math.random()*12)+'px',duration:0.1});});},80);

const cn=document.getElementById('ecg'), cx=cn.getContext('2d'); let w,h,dt=[],id=0,cv=500,cHx='#00e5ff';
function rsz(){w=cn.width=cn.offsetWidth;h=cn.height=cn.offsetHeight;dt=new Array(w).fill(h/2);} rsz(); setTimeout(rsz,2000); window.addEventListener('resize',rsz);
function dE(){
  cx.clearRect(0,0,w,h); let v=h/2, ab=(cv<250||cv>800), m=Math.floor(id)%80;
  if(ab)v+=(Math.random()-0.5)*h*0.8; else{if(m==20)v-=h*0.4;else if(m==23)v+=h*0.8;else if(m==28)v-=h*0.3;else v+=Math.sin(id*0.2)*4;}
  dt[Math.floor(id)%w]=v; id+=1.7; if(Math.floor(id)>w*10)id=0;
  let g=cx.createLinearGradient(0,0,w,0); g.addColorStop(0,'transparent'); g.addColorStop(0.2,cHx); g.addColorStop(0.8,cHx); g.addColorStop(1,'transparent');
  cx.beginPath(); cx.strokeStyle=g; cx.lineWidth=3; cx.lineCap='round'; cx.lineJoin='round';
  for(let i=0;i<w;i++){let p=dt[(Math.floor(id)+i)%w];if(i===0)cx.moveTo(i,p);else cx.lineTo(i,p);}
  cx.stroke(); requestAnimationFrame(dE);
} dE();

/* CHARTJS */
Chart.defaults.font.family='Share Tech Mono'; Chart.defaults.color='#7388a1';
const cX=document.getElementById('cht').getContext('2d'), cD=new Array(40).fill(500);
const cht=new Chart(cX,{type:'line',data:{labels:new Array(40).fill(''),datasets:[{data:cD,borderColor:'#00e5ff',borderWidth:3,tension:0.4,pointRadius:0,fill:true}]},options:{responsive:true,maintainAspectRatio:false,plugins:{legend:{display:false}},animation:{duration:250},scales:{x:{display:false},y:{min:0,max:1023,grid:{color:'rgba(255,255,255,0.03)'},border:{display:false}}}}});

/* ALERT CORE SYSTEM */
const C={
  0:{h:0x00e5ff,c:'#00e5ff',rgb:'0,229,255',m:'SYSTEM NOMINAL',s:0,ov:'transparent'},
  1:{h:0xeab308,c:'#eab308',rgb:'234,179,8',m:'ACOUSTIC ANOMALY',s:2,ov:'rgba(234,179,8,0.1)'},
  2:{h:0xf97316,c:'#f97316',rgb:'249,115,22',m:'HEART LOGIC WARN',s:3,ov:'rgba(249,115,22,0.15)'},
  3:{h:0xef4444,c:'#ef4444',rgb:'239,68,68',m:'ENGINE CRITICAL',s:6,ov:'rgba(239,68,68,0.25)'}
};
let lA=0, sAct=false, cShk=null, pT=0, coreP=gsap.to('#cr-wp',{scale:1.06,duration:0.8,repeat:-1,yoyo:true,ease:"sine.inOut"});
let ch=0; const hV=document.getElementById('h-val'), sT=document.getElementById('s-txt'), sB=document.getElementById('s-bdg');
function tk(){if(Math.abs(ch-cv)>2){ch+=(cv-ch)*0.15;hV.innerText=Math.round(ch);}else{ch=cv;hV.innerText=cv;}requestAnimationFrame(tk);} requestAnimationFrame(tk);

async function pd(){
  try{ const r=await fetch('/data?_='+Date.now(),{cache:'no-store'});
       if(r.ok){ const d=await r.json(); cv=d.heart; snd=!!d.sound; let aT=d.alertType; let A=C[aT]; cHx=A.c;
         sT.innerText=snd?'DETECTED':'SILENT'; document.documentElement.style.setProperty('--hud-c',A.c); document.documentElement.style.setProperty('--hud-r',A.rgb);
         if(sph){sph.material.color.setHex(A.h);iSph.material.color.setHex(A.h);}
         if(aT>0){
           if(lA!==aT){ lA=aT; sB.innerText=A.m; if(cShk)cShk.kill();
              cShk=gsap.to('body',{x:`random(-${A.s},${A.s})`,y:`random(-${A.s},${A.s})`,duration:0.05,repeatRefresh:true,repeat:-1,yoyo:true});
              if(!sAct){sAct=true;gsap.to('#ov',{background:A.ov,duration:0.3,repeat:-1,yoyo:true});coreP.timeScale(2.5);} else{gsap.to('#ov',{background:A.ov,duration:0.3,overwrite:"auto"});}
              
              if(aT===1){spk("Noise Alert",1.1);}
              else if(aT===2){spk("Heart Alert",1.1);}
              else if(aT===3){
                spk("Critical Alert",1.1); pT=Date.now();
                setTimeout(()=>{if(lA>=3){pSr(); setTimeout(sSr,6000);}}, 1800);
              }
           }
           if(aT>=3 && Date.now()-pT>15000){
              spk("Critical Alert",1.1); pT=Date.now();
              setTimeout(()=>{if(lA>=3){pSr(); setTimeout(sSr,6000);}}, 1800);
           }
         } else {
           if(lA!==0){ lA=0; sB.innerText=A.m; sSr();
              if(sAct){sAct=false;if(cShk)cShk.kill();gsap.to('body',{x:0,y:0,duration:0.1});gsap.killTweensOf('#ov');gsap.to('#ov',{background:'transparent',duration:0.4});coreP.timeScale(1);}
           }
         }
         cD.push(cv);cD.shift();cht.data.datasets[0].borderColor=A.c; let gr=cX.createLinearGradient(0,0,0,250); gr.addColorStop(0,`rgba(${A.rgb},0.4)`); gr.addColorStop(1,'transparent');
         cht.data.datasets[0].backgroundColor=gr; cht.update();
       }
  }catch(e){} setTimeout(pd,500);
}

let puT="", puH="", puR="", puA="";
async function ps(){ try{ const r=await fetch('/stats',{cache:'no-store'}); if(r.ok){ const d=await r.json(); 
  let nr=d.readings.toLocaleString(), na=d.alerts.toLocaleString(), nh=(Math.round((d.freeHeap||0)/1024)), nt=d.uptime;
  if(puR!==nr){scrmbl(document.getElementById('u-r'),nr,600); puR=nr;} if(puA!==na){scrmbl(document.getElementById('u-a'),na,600); puA=na;}
  if(puH!==nh){scrmbl(document.getElementById('u-h'),nh,600); puH=nh;} if(puT!==nt){scrmbl(document.getElementById('u-t'),nt,600); puT=nt;}
}}catch(e){} setTimeout(ps,2000); }

async function pl(){ try{ const r=await fetch('/logs',{cache:'no-store'}); if(r.ok){ const d=await r.json(), ls=document.getElementById('lgs'); if(!d.length)ls.innerHTML='<div style="color:var(--tx-d);">Logs empty</div>';
else{ls.innerHTML=d.map(x=>{let ty=x.type;let m=ty.includes('CRIT')?`<span style="color:#ef4444">`:(ty.includes('NORMAL')?`<span style="color:#10b981">`:`<span style="color:#f97316">`); return `<div class="li"><span class="li-tm">${x.time}</span><span class="li-ty">${m}${ty}</span></span><span style="color:var(--tx-d)">V: <b style="color:#fff">${x.heart}</b></span></div>`;}).join('');}
}}catch(e){} setTimeout(pl,3000); }
</script></body></html>)rawhtml";

#endif // MEDIPULSE_DASHBOARD_H
