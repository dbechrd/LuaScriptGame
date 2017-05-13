text = TextEngine:Instance();

function Joe_Talk ( dir, name )
        --UP
        if dir == 0 then
                text:Textbox( "Joe [UP]", "Hi " .. name, 1000, 30, 430 );
        --DOWN
        elseif dir == 1 then
                text:Textbox( "Joe [DOWN]", "Hi " .. name, 1000, 30, 430 );
        --LEFT
        elseif dir == 2 then
                text:Textbox( "Joe [LEFT]", "Hi " .. name, 1000, 30, 430 );
        --RIGHT
        elseif dir == 3 then
                text:Textbox( "Joe [RIGHT]", "Hi " .. name, 1000, 30, 430 );
        end
end