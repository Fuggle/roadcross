local playerBlue
local playerRed

function loadGame()
	playerBlue = 50
	playerRed = 50
end

function drawObjects()
	love.graphics.setColor(255, 0, 0);
    love.graphics.circle("fill", 300, 300, 10, 40);
    love.graphics.circle("fill", 300, 330, 10, 40);
    love.graphics.circle("fill", 300, 360, 10, 40);
    love.graphics.circle("fill", 300, 390, 10, 40);
    love.graphics.circle("fill", 300, 420, 10, 40);

	love.graphics.setColor(0, 0, 255);
    love.graphics.circle("fill", 300, 270, 10, 40);
    love.graphics.circle("fill", 300, 240, 10, 40);
    love.graphics.circle("fill", 300, 210, 10, 40);
    love.graphics.circle("fill", 300, 180, 10, 40);
    love.graphics.circle("fill", 300, 150, 10, 40);
end

function updateObjects(dt)
end

function love.keypressed(key, unicode)
	print(key)
	if key == "w" then
		--player Blue
		if checkScore(playerBlue) then 
			playerBlue = playerBlue + 1
			playerRed = playerRed - 1
		end
	end
	if key == "up" then
		--player Red
		if checkScore(playerRed) then 
			playerRed = playerRed + 1
			playerBlue = playerBlue - 1
		end
	end
	print("--BLUE--")
	print(playerBlue)
	print("--RED--")
	print(playerRed)
	print("-------")
end

--check that the sum of the players' score is not more than 100
function checkScore(player)
	if playerBlue + playerRed == 100
		and player >= 0 
		and player < 100 then
		return true
	else 
		return false
	end
end