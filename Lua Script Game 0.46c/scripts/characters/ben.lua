text = TextEngine:Instance();

function Ben_Talk ( dir, name )
        --UP
        if dir == 0 then
                text:Textbox( "Ben [UP]", "Hi", 1000, 30, 430 );
        --DOWN
        elseif dir == 1 then
                text:Textbox( "Ben [DOWN]", "Hi", 1000, 30, 430 );
        --LEFT
        elseif dir == 2 then
                text:Textbox( "Ben [LEFT]", "Hi", 1000, 30, 430 );
        --RIGHT
        elseif dir == 3 then
                text:Textbox( "Ben [RIGHT]", "Hi", 1000, 30, 430 );
        end
end