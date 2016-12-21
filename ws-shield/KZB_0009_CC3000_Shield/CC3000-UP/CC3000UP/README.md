CC3000UP
========
<h1>
	WARNING: 升级失败将导致 CC3000 无法继续使用，请慎重！升级过程中请使用外接 3.3v~9v 1A&nbsp;电源供电！</h1>

<p>
	<span style="color:#FFFFFF;"><span style="background-color:#FF0000;">​</span></span></p>

<p>
	本程序将 CC3000 模块固件版本升级到 &nbsp;TI CC30000&nbsp;Service Pack Version 1.24 Release Package 1.11.1</p>

<p>
	&nbsp;</p>

<h3>
	升级步骤：</h3>

<p class="rtecenter">
	<img alt="" src="http://www.tonylabs.com/uploads/images/product/CC3000/TONYLABS-CC3000-Patch-Upgrader.PNG" style="width: 482px; height: 444px;"></p>

<ol>
	<li>
		&nbsp;如果 Arduino IDE 正在运行，请退出 Arduino IDE 程序，确认所有的 Arduino 窗口都已关闭</li>
	<li>
		如果已经安装了 Adafruit CC3000 库，请先将库文件<span style="color:#FF0000;">移出 libraries 文件夹</span>，否则将无法成功编译本固件升级程序。</li>
	<li>
		打开本固件升级程序 ino 文件，修改 CC3000_IRQ, CC3000_VBAT, CC3000_CS 对应的引脚编号</li>
	<li>
		将 TONYLABS CC3000 扩展插入 Arduino Uno</li>
	<li>
		编译并上传程序到 Arduino Uno</li>
	<li>
		待上传完成后，打开串口工具，<span style="color:#FFD700;">设置波特率为 115200</span></li>
	<li>
		串口工具中输入<span style="color:#FFD700;"> 0</span>，点击发送（Send），在返回结果中查看当前 CC3000 模块信息</li>
	<li>
		串口工具中输入<span style="color:#FFD700;"> 4Y</span>，备份 CC3000MODR 的 EEPROM 数据到 Arduino 的 EEPROM 中</li>
	<li>
		串口工具中输入 <span style="color:#FFD700;">6Y</span>，擦出 CC3000MODR 的 EEPROM</li>
	<li>
		串口工具中输入<span style="color:#FFD700;"> 7Y</span>，可从 Arduino 的 EEPROM 中恢复 CC3000MODR 信息</li>
	<li>
		串口工具中输入<span style="color:#FFD700;"> 8Y</span>，更新固件第一部分 （Driver Patch 驱动升级）</li>
	<li>
		串口工具中输入 <span style="color:#FFD700;">9Y</span>，更新固件第二部分（Firmware Path 固件升级）</li>
	<li>
		串口工具中输入<span style="color:#FFD700;"> 0</span>，再次验证 CC3000MODR 的固件版本</li>
</ol>

<p>
	&nbsp;</p>

<p>
	对于 0-3 选项，可直接输入对应的数字，并直接回车或者点击 ”发送”，对于 4-9 选项，如果需要二次确认，可以先输入数字 4-9，后输入大写 Y 或 D 确认执行或取消命令。</p>

<p>
	如果 CC3000MODR 可以初始化，但是无法读取 MAC 地址和固件版本，可通过一下方式尝试修复：</p>

<ol>
	<li>
		重新启动 Arduino IDE</li>
	<li>
		输入<span style="color:#FFD700;"> 5D</span>，生成 TI 默认的随机 MAC 地址</li>
	<li>
		输入<span style="color:#FFD700;"> 6Y</span>，擦除当前 CC3000MODR 中的固件</li>
	<li>
		输入<span style="color:#FFD700;"> 7Y</span> ，将 Arduino 中 EEPROM 数据恢复到 CC3000MODR</li>
	<li>
		串口工具中输入<span style="color:#FFD700;">&nbsp;8Y</span>，更新固件第一部分 （Driver Patch 驱动升级）</li>
	<li>
		串口工具中输入<span style="color:#FFD700;">&nbsp;9Y</span>，更新固件第二部分（Firmware Path 固件升级）</li>
	<li>
		串口工具中输入&nbsp;<span style="color:#FFD700;">0</span>，再次验证 CC3000MODR 的固件版本</li>
</ol>