local playerBlue = 5
local playerRed = 5

function loadGame()
	playerBlue = 5
	playerRed = 5
end

function drawObjects()
    bluePlace = 420;
    redPlace = 150;


  	for i=1,playerBlue,1 do
  		love.graphics.setColor(255, 0, 0); --blue
    	love.graphics.circle("fill", 300, bluePlace, 10, 40);
		bluePlace = bluePlace - 30;
  	end

  	for i=1,playerRed,1 do
  		love.graphics.setColor(0, 0, 255); --red
    	love.graphics.circle("fill", 300, redPlace, 10, 40);
    	redPlace = redPlace + 30;
  	end

end

function updateObjects(dt)
end

function love.keypressed(key, unicode)
	print(key)
	if key == "w" then
		--player Blue
		if checkScore(playerBlue) then 
			playerBlue = playerBlue + 1;
			playerRed = playerRed - 1;
		end
	end
	if key == "up" then
		--player Red
		if checkScore(playerRed) then 
			playerRed = playerRed + 1;
			playerBlue = playerBlue - 1;
		end
	end
	print("--BLUE--");
	print(playerBlue);
	print("--RED--");
	print(playerRed);
	print("-------");
end

--check that the sum of the players' score is not more than 100
function checkScore(player)
	if playerBlue + playerRed == 10
		and player >= 0 
		and player < 10 then
		return true
	else 
		return false
	end
end