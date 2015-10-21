--Script support
titleAdds = { "We have Lua!", "Candy is actually popcorn...", "Unicorn's are illegal?" }
math.randomseed(os.time())
function randElem(T)
    return T[math.random(#T)]
end

init = {
  --[gfxConfig]
  windowTitle = "NinjaCade - " .. randElem(titleAdds),
  fallbackTitle = "NinjaCade",

  --[renderConfig]
    --1920x1080 when?
  clientWidth = 1200,
  clientHeight = 900,

  --[debugMode]
  debugMode = true,
}

--print (init.windowTitle)
print (randElem(titleAdds))
return init