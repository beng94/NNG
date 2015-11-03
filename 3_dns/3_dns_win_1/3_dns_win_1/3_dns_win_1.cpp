#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

char bin_to_char(int c)
{
	switch (c)
	{
	case 0: return 'A'; break;
	case 1: return 'C'; break;
	case 2: return 'G'; break;
	case 3: return 'T'; break;
	}
}

std::string decode_ascii(char c)
{
	std::string out;
	out += bin_to_char(c & (3));
	out += bin_to_char((c & 12) >> 2);
	out += bin_to_char((c & 48) >> 4);
	out += bin_to_char((c & 192) >> 6);

	return out;
}

int main()
{
	std::string b = R"**(A0{��}0yuxx0q{qd��y}��q090��{g}obv��xqdqyuxx0q{qd��y}��q/Ao0uyx��0q0yuxx~qbwqxz{80q0bouvmrbz{d0bo��xu0��b0qo0ux��xb��0|��{qxgz{qx0~��o��dd0ux|uxmuo~ut��0y}c}vmub0boucg;0Axq~��d0q0g��xdzo��0yu{{m}b��vsu{0xucq~��tzdd0ob��cbo��gud0��b0q0~��d��bo��gud0qc��{mq0|qd��czooq0yuv;0R��xmq0!% 9"  0vcqyy80uo0boz`dqd��b0qxqdd0d��ssbo��c��b��cu0{��gu~ut|ud;0��xuddq{}0uxu{b��v80|zvm0q0yuxxu~0c}d~��{0uvmwzcy��~80y��cud��~0uxd��c0b0uo0qo0uxd��c��b0duc|ubb��v0ed��{0wz~zo��t|qd;0Ao0uyx��d0g��~z{m0s��c0szc��dq80yuxm0q0s}ys��etgqc0duc��xud��{0~��x��{s��o��0wz~sq{0`}vyu{d��xd80}dd0wqvvm��90��b0gucud��~y}c}vmu~ud80c}d~��{0bo��cd��bo��~ud0}b0dqcdqxyqo;A0s}ys��etgqc0~��ou`��s��x0uyux~ut}~0ux��0q0yuxxs}ys��80yuxm{u~0dudu��{0`z{dbouc��0{m��x��bbqx0{m��x{q~0qo0uyx��y}c}vm0~}guoud��rb��gu}80q0durbqdzc{��~;0A0yuxxs}ys��sq{0dqx��x|qd��0b}yq0}oyz~0}{vucx��bcu0��bbou|��o��t{q~0��b0q0s}ys��d0~}uyux}~;0Mxmu{0}{vuc0xu|ud0q0rburbuy��0boz`dqd��bq80q0|}tuv80q0boule��x}b0}ovqxzy;A0yuxx0wux��`��d��b��su{0|��czy0w��0qx~zd��c��bo0��dbo}~0t��{d��0boucu`ud/90I}c}vmbo��gud80qy}0!%9# 0bevqcqbq{0ux|uxmuo~ut��0xusu{ms��x0��xx;0I��cudu0{uy0duc|ub0��xxq`zdsq{0{uy0{qvmzss80y}{d0q0s}ys��etgqc80boz`dqd��b0}tu��{0qoz{sq{0uxu{d��bu{0yuv{qvmzsszt}~;90N��d��bo��gud}0��xxzy��{m80yuxm0qo0uyx��0d��yqbo��d0qtq80wzcy����d0s}odzb��dq;90_b��cbo��gud80qyuxm0q0y}c}vmu~0��b0q0~��d��bo��gud}0��xxzy��{m0~��o��dd}0duc��xudud0d��xd}0~}80qo0��xud~zc0ux��cu|qxqtd��gqx0yu{{m}b��vu0q0y}c}vmu~0czg��b��cq0{��gu~bo}~;E0|��czy0qx~zd��uxuy0qc��{mq0boqsq0yuv0q0yuxxu~0y��cud��d80qxq~��d80wuboubb��v��d80��bboubb��v��su{0uvm��{}0uxxuyo��}d;Ao0uyx��{u~0bq��d0}ozyoqdq0{}{rb80rbe`��{0q0s��c0dqcdq0��b0q0~��d��bo��gud}0��xxzy��{m0c��vo��d}0q0yuxx~qbwqxz{;0Ao0uyx��~0g��c90��b0{m}cz~uxx��d��bq80gqxqy}{d0su}tuvo��bu0}vu{0vqotqv;0A0{m}cz~uxguoud��b0{qvmc��bod0q0|��{qx}0{m}cz~rbzy��~0wux��0d��cd��{}~;A0yuxx0��xuddq{q/Ao0uyx��y}c}vmu~0y��~��t��bu0q0buct��x��~zcd��x0q0g��xdzo��b0~zc��}v0|zcyz{��x}b0suwzxm��b0qxqdd0��xx;0Gux{��dd0{��{0qo0uyx��0��xxzy��{mq0q0|qg}0r}~xeb0bzc��{0wzxmqyqdzbq{0g��xdzo}~0q0|zcyz{|qd��b{q~0yuvwuxux��u{;0Eo��cd0wz{dzb0`��xt��ex80|zvm0qo0uyx��0��{g}obv��xqd��d0y}{t}v0q0r}~xeb0qoz{zb0}t��`z{d��sq{0g��vuoo��~;0A0|zcyz{ducyux��bd0q0~��o`z{d}0}tuvcu{tboucsu{0q0|}`zdqxqyebo0��b0qo0qvmqxq`}0y}c}vm0boqs��xmzooq;0Ao0uyx��0��xxzy��{m��cq0q0xuvwz{dzbqss0suwzxm��bd0q0`uduw��bou~su{0ducyux��t��0|zcyz{z~0vmq~zczx��~/0qo0��bodczv��{0<d��bo��|zcyz{=0��b0q0`czvuboducz{0<b��cvqdubd|zcyz{=;Ao0��bodczv��{u~0buc~u{d}~0q0y}c}vm|��y0wux��t��b��d80q0s}ys��0{��gu~ut��b��d80`}vyu{d��r}����{q~0wz~zo��t��b��d;0Lqd��be~cq0q0yuxx0yuv{qvmzsszt}~80wuboubb��80d��y��dd��0g��x}~;0A0r}~xeb0y��bzt}~0wux��su{0bz~0{��{��x0`q{qboz~qd0z~zo|qd0qo0uyx��0��co��~u{mb��vu80teooqt��bq80qy}0qo0��bodczv��{0z~zodq0wzxmqt��~9g}bboqdqcd��b0~��gud~uoy��{mu;0A0`czvuboducz{0rb��~~u{d}0qo0��bodczv��{|qd��bd80ux��buv��d}0q0durbqdzc{��~0wux��t��b��d80u{m|��d}0q0yu{bdce��r}��gqx0��bbouw��vv��0wzxmqt��~9g}bboqdqcd��bd;A0~��d0|zcyz{d��`eb0uvmy��bd0c��bosu{0~}uv��bo��dgu80c��bosu{0v��dzxgq0boqs��xmzooq0q0yuxx0y��~��t��b��d;Ao0qvmqxq`}0y}c}vmsu{0ducyux��t}~0q0`czxqrd}{0{ug��0|zcyz{;0A0duc|ubb��v0qxqdd0��b0q0boz`dqd��b~zc0gq{0uxu{d��b��vu80q0duuxg��xqbod��b��cd0wuxux��b;A0yuxx0��b0q0yu{bdce��r}��b0r}~xeb/A0{��~0{qvm0c��bou0bo}{du0{q`cq~��bou{0detq0~��gud{}0r}~xeb��{q~0��xxq`zd��d0yuxxu}{u~0g��xdzo��bq}s��x;A0yu{oubo0qxqdd0��b0{��|��{m0{q``qx0ed��{q0q0~��d0w��0|zcyz{wqdq0<qo0��bodczv��{u~0��b0q0`czvuboducz{=0qxqrbz{m0bo}{du{0��xx{q~80}xmu{~zc0q0yuxxu~0teooqt��bq0yuvbo��{}~80q0y}c}vmu~0g}bboqwux��t{u~;0Eo0qo0}t��`z{d0q0xuvqx~qxyqbqss0q0yuxxu~0��{g}obv��xqd��cq80y}gux0}xmu{~zc0qo0uyx��~0��x0��ddq`}{d|qd��q~;0A0r}~xeb0! ;0{q`q0~��c��x0qo0��bodczv��{ducyux��b0wz~zo��t}~80q0budu~0boq`zczt��b{q~0}{tex{q~80yuv~uot��t}~0q0yuxxu~0teooqt��bq;)**" "\r"
		R"**(A0`czvuboducz{sq{0vqotqvqss0dqsxudd��~0uxxu{~uo��0|qd��bd0g��xdq{q~0~};Ayu{{m}su{0qo0uyx��`q{qboz~0dqcd��bq{0wu{{��xx{q~80q~~zc0buy0~uxx0xuyz{tq{}0q0dqsxudd��b0wzvqyo��bv��dx��bc��x10N��ct0{��vm��vm��bozt0buv��db��v��d80y}gux0}xmu{~zc0��ctuyub0qxqrbz{mqss0��bodczv��{dqcdqxy��0dqsxudd��cq0��dd��c{};0A0yq}0~zcbouc��0dqsxudd��~80qyuxmu~su{0qo0��bodczv��{dqcdqxzy0y}{}y��x}b80y��c0}vu{0c}d~��{0z~zoo��~0u0~uxxuyudxu{0yuxx��~|qd��bd80evmq{q~~zc0wzvqyo��bv��dx��0|qd��be~0s}odz{b��vq0~}g��x��;0A0wzvqyo��bv��dx��0dqsxudd��~0dqcd��b0qx~qxyqo��bq0g��t��|qd��bd0wud0~}0qo0uyx��0��}{texqd��0yuvsuduvut��bu}gux0bouysu{;0Mxmu{0yuvsuduvut��b0q0w}sczr}bod��b0uyx��suduvb��v0<yqbodz`��d}q=0��b0q0w}sczqtu{zyq;0#9$0��gub0dqsxuddqbout��bd0~��gud��u{0q0|qd��b0y��c0~}yedqd|qd��;A0g��t��0|qd��b0gqx��bo��{��xuv0q0dqsxudd��~sq{0xug��0b��cvqdubd|zcyz{{q~0<`czvuboducz{=0~��bo��{|ud��;0Rq{zb80{uy0}vqozxd��~80|zvm0q0dqsxudd��{q~0qo0uyx��0czbbo}{texqd��0suduvb��vu}cu0}b0g��t��0|qd��bq0xu{{u;0��gd}outu~}v0dqcd��80{qvm0suduvx��dbo��y��0g}obv��xqdz~0ed��{0q0~��ct��b0y}{ty��}v0{uy0uxt��{d��dd;0Ouxu{xuv}0detzy��be{~0bouc}{d0q0wzvqyo��bv��dx��d0bout��0{��~{��x0y}{}y��x}bq{0{qvmzss0qo0uyx��c��~0~zr~��oqdq80y}{d0dqsxudd��d0{uy0bout��0~zcd��cbq}~{��x;0A0wzvqyo��bv��dx��0bout��b��{u~0qssq|qvm��bq0ed��{0! 0��g0qxqdd0yuvbo��{}~0uo0q0rbu~��xm0~��x��{sb��v;0Kuy0}byucd80|zvm0gqx��sq{0q0~��bo��dy��{m0z~zooq9u0qo0uyx��c��~0vmq~zc}b��v��{q~0~}by��cd��~��0{��gu~ut��b��d;0G}vmuxuysu0~uxx0gu{{}0qod0}b80|zvm0q0dqsxuddqbout��0{��~0vmq~cqssq{0��c{q~0{��vm��vm��boqd}0uxxu{��co��bcu80��vm0ubud��~su{0q0tqvq{qd0wuxwutuo��b��{u~0ub��xmu}0}b0{qvmzssq~;A0yuxx0��{g}obv��xqdqA0yuxx0��{g}obv��xqd��d0~��ogudxu{��x0q0yu{bdce��r}��0ed��{0r��xbouc��0g��vuo{};0Mxmu{~zc0qo0uyx��~0��x0��ddq`}{d|qd��q~80{uy0��co��~u{mu~;0Gz{dzb80|zvm0cu{tboucubu{80y}{tu{0|��{q`sq{0qoz{zb0}t��su{0g��vuoo��~0qo0��{g}obv��xqdzd;0A0g}obv��xqd0yuvdu~}{d��bs��x0��b0dq`}{d��bs��x0dug��t}~0��bbou;!;0Ao0uyx��~0yuvdu~}{d��bu0q0d��~��csu{/Wud~��oo0xu0tuc��~}v80��xx0gqvm0��x0uc��b0w��{msu{0q0d��~��c0ux��;0A0yuxxu~0yuvdu~}{d��bu~zc0{u0wuxutt80|zvm0qo0uyx��~0bzbuy0duxubu{0uvmwzcy��~;I}cu0~uxx0w}vmux{}*90H��dbo9u0g��xdzo��bd0yuxxu}t0y��cud��su{80qxq~��sq{*90Wq{9u0g��xdzo��b0qo0uyx��s}ys��~z{80q0s}ys��etgqcsq{*90Wq{9u0g��co��b0gqvm0g��xqt��~zo��b0gqxqyuxm}~0uyx��s}ys��s��x*090Wq{{q~9u0boz~qdxq{0s��cuxg��xdzo��bz~80su|��o��t��bz~80~}uyux~ut��bu~q0yuxxu}tu{*90Wq{9u0utt}v0{uy0��boxuxd80ubudxuv0ux��uyux~ut��0��ccqozxqd0q0yuxxu~u{*A0wu{d}0~��ct��bu~cu0q0g��xqbod0q0d��~��csu{0dqx��xzt0yuv0q0~��gud~uo��0y��tz{/!;0H��vqbt0xu0xqo��{0q0~qcq}tqd80du~}{dbt0yuv0q0yuxxu}tud;#;0Eyuxt0wux0~qcq}tqd0q0wuut0w��x��80y}~��osu{0uvm}~0zxtqxc��x0q0y��b}~cq0wzctexbo80~��gubt0q0yuxxu~0~z{d��c��{q~0g��xdzo��bq}d0~��x��{s��o��0bo��vu~s��x0yuvdu~}{dgu0qoz~qd;";0E{m|��{0`c��buxt0��bbou0q0yuxxs}ys��~qd0{}{rb9u0g��co��b80g��xqt��~zo��b0sux��x��~*0Ao0uyx��0��ddq`}{d��bq/!;0Gu~��t0~��{muxyubu{0|q{mqdd80wuut0qxqdd0uvm0`��c{��gqx;0A0g}obv��xq{t��0zxtqxz{0uyuxt0~}0xq`zr~��tqd0uvm0��bbou|qdzdd0d��c��x~��o��gux80��vm0~��{{mussu{0dq`}{d|qdzt0��d0q0yuxxut;0A0yuxxu~0g}obv��xqdq0qo0uxxu{zxtqx}0~��ooux0d��cd��{u{80qo0��``u{0{uy0|qbo{��xd0~uout0dutt0q0wuut0qx��;#;0��bbouo��cd0eq}t0uv��bo0qxb��0wux��xud��d0|qbo{��xt0q0dq`}{d��b|zo80{u0rbq~0qo0esuvmu~ud;0A0dq`}{d��bd0q0~exrbrbz{dd��x0~uott80xuwux��0|qxqtgq;0Uq}t0~��c~��c��bu{0yzozvq{q~0uvm0~��`ouxudsux}80bo��~��x��0b`}c��x0yu{d��{80yuxm{u~0~��o��``z{dq80uo��xdqx0q0dq`}{d��b}0y��guxud0g��v`z{dq0q0yuxxs}ys��;0W}vm��oo80uvmudxu{0duc��xud0bu0yqcqtz{0~}0q0g}obv��xqd0bzc��{1";0Lq0y}{t~��d0yuxxut0��ddq`}{dzddqt80|qbz{x��0yzotexqdz~~qx0dq`}{dbt0��d0q0|��{qxq~qd80q0|��{qxy��xmut��bd��x0}{texgq80q0yuxxu~0}c��{m��sq{0|qxqtgq;A0"0~��`0~��od}0~��x��{sb��v0qssq{0gq{80|zvm0q0wux��x��{~0xug��0yuxxud0q0y��b}~0~uo��gux0|zx0wzvq/0Ayu{{m}su{0q0g}obv��xqd0bzc��{0utt}v0{uy0��boxuxd0rbzy��d80d��y��c��x��bd0dq`}{dq{��x80q~��c0q0yuxxsu{80q~��c0q0|��{qx��cz~sq{80}xxudgu0s��cy}xmu{0uvm��s0uxg��xdzo��bd0wutuo{��x0wux80wzctex0{��vm��vm��bo0~uoux��zcgzb|zo1)**";

	std::ofstream file("decoded_dns.txt");

	for (auto c : b)
	{
		file << decode_ascii(c);
		//std::cout << decode_ascii(c);
	}

	file.close();

	return 0;
}