io.stdout:setvbuf("no") --console printouts (DEVELOPMENT ONLY)

-- Libraries
Gamestate = require "libs.hump.gamestate"
Timer = require "libs.hump.timer"

-- Game states
Game = {}

-- Stored info
Players = {}

-------------------------------------------------
--                main/defaults                --
-------------------------------------------------

function love.load()
	print("LOVE LOADED")
	Gamestate.registerEvents()
	Gamestate.switch(Game)
end

function love.update(dt)
	Timer.update(dt)
end


-------------------------------------------------
--                    game                     --
-------------------------------------------------

function Game:enter()
	require "game"	

 	print("Game enter")

	loadGame()
end

function Game:draw()
	
	drawObjects()
end

function Game:update(dt)
	updateObjects(dt)
end