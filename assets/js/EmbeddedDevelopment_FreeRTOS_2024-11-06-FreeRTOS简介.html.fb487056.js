"use strict";(self.webpackChunklearn_data=self.webpackChunklearn_data||[]).push([[1783],{8295:(e,r)=>{r.A=(e,r)=>{const t=e.__vccOpts||e;for(const[e,S]of r)t[e]=S;return t}},6071:(e,r,t)=>{t.r(r),t.d(r,{comp:()=>o,data:()=>i});var S=t(4691);const a={},o=(0,t(8295).A)(a,[["render",function(e,r){return(0,S.uX)(),(0,S.CE)("div",null,r[0]||(r[0]=[(0,S.Fv)('<h2 id="_1-什么是freertos" tabindex="-1"><a class="header-anchor" href="#_1-什么是freertos"><span>1.什么是FreeRTOS？</span></a></h2><p>FreeRTOS是一个热门的嵌入式设备用即时操作系统核心，它于2003年由Richard Barry设计，并已被经成功移植到35种不同的微控制器上。</p><p>ESP32系列中的FreeRTOS和原始FreeRTOS有所不同。原始FreeRTOS是一款小巧高效的实时操作系统，适用于许多单核MCU和SoC。但为了支持双核ESP芯片，如ESP32、ESP32-S3、ESP32-P4，ESP-IDF特别提供了支持双核对称多处理 (SMP) 的 FreeRTOS 实现。</p><h2 id="_2-为什么学习freertos" tabindex="-1"><a class="header-anchor" href="#_2-为什么学习freertos"><span>2.为什么学习FreeRTOS？</span></a></h2><p>对于ESP32系列单片机而言，ESP-IDF在系统启动时会默认启动FreeRTOS。因此，如果我们想要高效地利用ESP32系列丰富的硬件资源，使用FreeRTOS几乎成为一种必然。此外，随着嵌入式硬件性能的不断发展，FreeRTOS所占用的系统资源比重越来越小，FreeRTOS已不再成为嵌入式硬件性能的负担。相反，RTOS提供的事件驱动型设计方式，使得RTOS只是在处理实际任务时才会运行，这能够更合理的利用CPU，也有利于实现日益发展的低功耗技术。在实际项目中，如果程序等待一个超时事件，传统的无RTOS情况下，要么在原地一直等待而不能执行其它任务，要么使用复杂（相对RTOS提供的任务机制而言）的状态机机制。如果使用RTOS，则可以很方便的将当前任务阻塞在该事件下，然后自动去执行别的任务，这显然更方便，并且可以高效的利用CPU。</p><p>但与此同时，FreeRTOS也有一定弊端：</p><ol><li>大多数RTOS代码都具有一定规模，任何代码都可能带来BUG，何况是代码具有一定规模的RTOS，因此引入RTOS的同时也可能会引入该RTOS的BUG，这些RTOS本身的BUG一旦被触发，影响可能是是灾难性的。</li><li>熟练的使用RTOS是一项技能，需要专业的知识储备和长期的经验积累。不将RTOS分析透彻，很容易为项目埋下错误。典型的，像中断优先级、任务堆栈分配、可重入等，都是更容易出错的地方。</li><li>RTOS的优先级嵌套使得任务执行顺序、执行时序更难分析，甚至变成不可能。任务嵌套对所需的最大堆栈RAM大小估计也变得困难。这对于很多对安全有严格要求的场合是不可想象的。</li><li>RTOS应该用于任务复杂的场合，以至于对任务调度的需求可以抵消RTOS所带来的稳定性影响，但大部分的应用并非复杂到需要RTOS。</li></ol><p>随着物联网的发展，未来的嵌入式产品必然更为复杂、连接性更强以及需要更丰富的用户界面。当处理这些任务时，一个好的RTOS就变得不可缺少了。</p><p>书到用时方恨少，我希望自己永远不会有这种感觉。</p><h2 id="参考" tabindex="-1"><a class="header-anchor" href="#参考"><span>参考</span></a></h2><p>1.<a href="https://docs.espressif.com/projects/esp-idf/zh_CN/v5.3.1/esp32s3/api-reference/system/freertos.html" target="_blank" rel="noopener noreferrer">ESP-IDF FreeRTOS概述</a></p>',11)]))}]]),i=JSON.parse('{"path":"/EmbeddedDevelopment/FreeRTOS/2024-11-06-FreeRTOS%E7%AE%80%E4%BB%8B.html","title":"FreeRTOS简介","lang":"zh-CN","frontmatter":{"title":"FreeRTOS简介","date":"2024-11-06T00:00:00.000Z","category":["ESP32","嵌入式开发"],"tag":["ESP32","嵌入式开发","FreeRTOS"],"order":-1,"description":"1.什么是FreeRTOS？ FreeRTOS是一个热门的嵌入式设备用即时操作系统核心，它于2003年由Richard Barry设计，并已被经成功移植到35种不同的微控制器上。 ESP32系列中的FreeRTOS和原始FreeRTOS有所不同。原始FreeRTOS是一款小巧高效的实时操作系统，适用于许多单核MCU和SoC。但为了支持双核ESP芯片，如...","head":[["meta",{"property":"og:url","content":"https://scaxlibur.github.io/EmbeddedDevelopment/FreeRTOS/2024-11-06-FreeRTOS%E7%AE%80%E4%BB%8B.html"}],["meta",{"property":"og:site_name","content":"Scaxlibur 博客"}],["meta",{"property":"og:title","content":"FreeRTOS简介"}],["meta",{"property":"og:description","content":"1.什么是FreeRTOS？ FreeRTOS是一个热门的嵌入式设备用即时操作系统核心，它于2003年由Richard Barry设计，并已被经成功移植到35种不同的微控制器上。 ESP32系列中的FreeRTOS和原始FreeRTOS有所不同。原始FreeRTOS是一款小巧高效的实时操作系统，适用于许多单核MCU和SoC。但为了支持双核ESP芯片，如..."}],["meta",{"property":"og:type","content":"article"}],["meta",{"property":"og:locale","content":"zh-CN"}],["meta",{"property":"og:updated_time","content":"2024-11-10T07:07:56.000Z"}],["meta",{"property":"article:tag","content":"ESP32"}],["meta",{"property":"article:tag","content":"嵌入式开发"}],["meta",{"property":"article:tag","content":"FreeRTOS"}],["meta",{"property":"article:published_time","content":"2024-11-06T00:00:00.000Z"}],["meta",{"property":"article:modified_time","content":"2024-11-10T07:07:56.000Z"}],["script",{"type":"application/ld+json"},"{\\"@context\\":\\"https://schema.org\\",\\"@type\\":\\"Article\\",\\"headline\\":\\"FreeRTOS简介\\",\\"image\\":[\\"\\"],\\"datePublished\\":\\"2024-11-06T00:00:00.000Z\\",\\"dateModified\\":\\"2024-11-10T07:07:56.000Z\\",\\"author\\":[{\\"@type\\":\\"Person\\",\\"name\\":\\"Scaxlibur博客\\",\\"url\\":\\"https://scaxlibur.github.io/\\"}]}"]]},"headers":[{"level":2,"title":"1.什么是FreeRTOS？","slug":"_1-什么是freertos","link":"#_1-什么是freertos","children":[]},{"level":2,"title":"2.为什么学习FreeRTOS？","slug":"_2-为什么学习freertos","link":"#_2-为什么学习freertos","children":[]},{"level":2,"title":"参考","slug":"参考","link":"#参考","children":[]}],"git":{"createdTime":1730892922000,"updatedTime":1731222476000,"contributors":[{"name":"Scaxlibur","email":"scaxlibur@gmail.com","commits":3}]},"readingTime":{"minutes":2.77,"words":831},"filePathRelative":"EmbeddedDevelopment/FreeRTOS/2024-11-06-FreeRTOS简介.md","localizedDate":"2024年11月6日","excerpt":"<h2>1.什么是FreeRTOS？</h2>\\n<p>FreeRTOS是一个热门的嵌入式设备用即时操作系统核心，它于2003年由Richard Barry设计，并已被经成功移植到35种不同的微控制器上。</p>\\n<p>ESP32系列中的FreeRTOS和原始FreeRTOS有所不同。原始FreeRTOS是一款小巧高效的实时操作系统，适用于许多单核MCU和SoC。但为了支持双核ESP芯片，如ESP32、ESP32-S3、ESP32-P4，ESP-IDF特别提供了支持双核对称多处理 (SMP) 的 FreeRTOS 实现。</p>\\n<h2>2.为什么学习FreeRTOS？</h2>\\n<p>对于ESP32系列单片机而言，ESP-IDF在系统启动时会默认启动FreeRTOS。因此，如果我们想要高效地利用ESP32系列丰富的硬件资源，使用FreeRTOS几乎成为一种必然。此外，随着嵌入式硬件性能的不断发展，FreeRTOS所占用的系统资源比重越来越小，FreeRTOS已不再成为嵌入式硬件性能的负担。相反，RTOS提供的事件驱动型设计方式，使得RTOS只是在处理实际任务时才会运行，这能够更合理的利用CPU，也有利于实现日益发展的低功耗技术。在实际项目中，如果程序等待一个超时事件，传统的无RTOS情况下，要么在原地一直等待而不能执行其它任务，要么使用复杂（相对RTOS提供的任务机制而言）的状态机机制。如果使用RTOS，则可以很方便的将当前任务阻塞在该事件下，然后自动去执行别的任务，这显然更方便，并且可以高效的利用CPU。</p>","autoDesc":true}')}}]);