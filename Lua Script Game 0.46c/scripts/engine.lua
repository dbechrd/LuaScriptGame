engine = GameEngine:Instance();
camera = Camera:Instance();
level = engine:LoadLevel("maps\\town.map");
player = Character:new("data\\characters\\ben.dat", 224, 32);
enemy = Character:new("data\\characters\\joe.dat", 224, 192);
--text = TextEngine:Instance();

level:Draw(1);
player:Draw();
camera:SetMode(1);
camera:SetChar(player);
enemy:Draw();
level:Draw(2);

cammode = 0;
follow = 1;
cpressed = 0;
inspecting = 0;
debug = 0;

function CutScene()
	camera:SetChar(enemy);
	--text:Textbox( "Hi there Player, I'm Robbie.", 30, 450 );
end

function HandleInput()
	--KeyPressed = engine:HandleInput();
	engine:HandleInput();
	
	if engine:KeyDown("esc") or engine:KeyDown("SDLQUIT") then
		engine:SetQuit();
	end

	--Camera Controls
	if engine:KeyDown("c") and cpressed == 0 then
		if follow == 0 then
			--if cammode == 0 then
			--	camera:SetMode(1);
			--end
			camera:SetChar(player);
			follow = 1;
		elseif follow == 1 then
			--if cammode == 0 then
			--	camera:SetMode(1);
			--end
			camera:SetChar(enemy);
			follow = 0;
		end
		cpressed = 1;
	elseif engine:KeyUp("c") then
		cpressed = 0;
	end

	if engine:KeyDown("d") then
		debug = 1;
	end

	if engine:KeyDown("v") then
		camera:SetMode(0);
		camera:SetPos(0, 0);
	end

	if engine:KeyDown("z") then
		camera:SetSize(480, 320);
	end

	if engine:KeyDown("x") then
		--camera:SetPos(0);
		camera:SetSize(640, 480);
	end

	if engine:KeyDown("q") then
		CutScene();
	end

	--Action Key
	if engine:KeyDown("return") and inspecting == 0 then
		player:Action();
		inspecting = 1;
	elseif engine:KeyUp("return") and inspecting == 1 then
		inspecting = 0;
	end

	--Enemy Controls
	if engine:KeyDown("i") then
		enemy:Walk("up");
	elseif engine:KeyDown("j") then
		enemy:Walk("left");
	elseif engine:KeyDown("k") then
		enemy:Walk("down");
	elseif engine:KeyDown("l") then
		enemy:Walk("right");
	elseif engine:KeyUp("i") and engine:KeyUp("j") and engine:KeyUp("k") and engine:KeyUp("l") then
		enemy:Walk("stop");
	end

	--Player Controls
	if engine:KeyDown("up") then
		player:Walk("up");
	elseif engine:KeyDown("left") then
		player:Walk("left");
	elseif engine:KeyDown("down") then
		player:Walk("down");
	elseif engine:KeyDown("right") then
		player:Walk("right");
	elseif engine:KeyUp("up") and engine:KeyUp("left") and engine:KeyUp("down") and engine:KeyUp("right") then
		player:Walk("stop");
	end

	
	
end

while GameEngine:Quit() == false do
	HandleInput();

	engine:Update();
	player:Update();
	enemy:Update();
	camera:Update();

	obj = player:CollidingWith();
	if obj ~= NULL then
		if obj:GetType() == 07 then
			obj:SetTile(0);
			obj:SetName("Wall");
			if debug == 1 then
				obj:SetCollide(false);
			end
		end
	end

	level:Draw(1);
	player:Draw();
	enemy:Draw();
	level:Draw(2);

	--engine:Sleep(-1);
end

--player:delete();
--enemy:delete();
--level:delete();
--engine:Sleep(2000);
--GameEngine:SetQuit();