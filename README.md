# Benchmark: Lua Binding

A benchmarking many of the canonical/best/popular lua bindings for their performance.

# Current Bindings

The following bindings are benchmarked or are being aimed to be benchmarked. All are built on top of plain C:

[x] - Plain C (PUC-RIO Lua 5.3.4)
[x] - sol1 (old_sol, from Rapptz)
[x] - sol2 (ThePhD, v2.20)
[x] - sol3 (ThePhD, latest)
[x] - luabridge (Vinnie Falco's latest)
[x] - OOLua (LiamDevine, forked at v2.0.1 (latest) from elite-lang since website is down (May 1st, 2018))
[x] - Lua-Intf (Steve K. Chiu, latest)
[x] - Selene (Jeremy Ong, forked at latest + patches)
[x] - Kaguya (satoren, latest)
[x] - Luwra (Ole Krüger, latest)
[x] - lua-api-pp (OldFisher, latest + patches)
[ ] - tolua++ (Ariel Manzur, Waldemar Celesm latest + patches)
[ ] - SWIG (Latest as of May 1st, 2018, maintained by various)
[ ] - luawrapper (Tomalak, maintained by , latest)
[ ] - luacppinterface (David Siaw, latest)
[ ] - luabind (Rasterbar, latest + patches)

If you feel there is a binding that needs to be benchmarked, please either make a pull request for that library or make an issue request. Please note that I am not particularly thrilled to benchmark libraries that cannot compile on Visual C++'s/g++'s/clang++'s latest compiler versions and have had quite my fill of hacking older, unmaintained libraries to make them compile for recent compilers.

If the library you suggest has no documentation and fills my terminal with errors I am likely going to throw it out the window.

I want _working_, _halfway decent_ libraries, not more things I need to make personal forks of in order for them to compile properly only to muck around in an undocumented mess. If you want something benchmarked, point me to some examples / documentation or just make a ready-made pull request. Follow any of the `{library-name-here}.cpp` files in the source folder to see an example. Some are hairy, so using `sol2.cpp` or `sol3.cpp` as an example of what we are benchmark is a good idea.
