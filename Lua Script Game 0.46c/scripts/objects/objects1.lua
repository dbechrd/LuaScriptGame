text = TextEngine:Instance();

function ObjInspect ( dir, obj, name )
        if obj == 00 then
                --UP
                if dir == 0 then
                        text:Textbox( name, "Ooo, I like green. (Front)", 1000, 30, 430 );
                --DOWN
                elseif dir == 1 then
                        text:Textbox( name, "Ooo, I like green. (Back)", 1000, 30, 430 );
                --LEFT
                elseif dir == 2 then
                        text:Textbox( name, "Ooo, I like green. (Right)", 1000, 30, 430 );
                --RIGHT
                elseif dir == 3 then
                        text:Textbox( name, "Ooo, I like green. (Left)", 1000, 30, 430 );
                end
        elseif obj == 01 then
                --UP
                if dir == 0 then
                        text:Textbox( name, "Plain ol' red apple. (Front)", 1000, 30, 430 );
                --DOWN
                elseif dir == 1 then
                        text:Textbox( name, "Plain ol' red apple. (Back)", 1000, 30, 430 );
                --LEFT
                elseif dir == 2 then
                        text:Textbox( name, "Plain ol' red apple. (Right)", 1000, 30, 430 );
                --RIGHT
                elseif dir == 3 then
                        text:Textbox( name, "Plain ol' red apple. (Left)", 1000, 30, 430 );
                end
        elseif obj == 02 then
                --UP
                if dir == 0 then
                        text:Textbox( name, "Wtf?!?! It's blue! (Front)", 1000, 30, 430 );
                --DOWN
                elseif dir == 1 then
                        text:Textbox( name, "Wtf?!?! It's blue! (Back)", 1000, 30, 430 );
                --LEFT
                elseif dir == 2 then
                        text:Textbox( name, "Wtf?!?! It's blue! (Right)", 1000, 30, 430 );
                --RIGHT
                elseif dir == 3 then
                        text:Textbox( name, "Wtf?!?! It's blue! (Left)", 1000, 30, 430 );
                end
        elseif obj == 03 then
                --UP
                if dir == 0 then
                        text:Textbox( name, "Nothin' wrong with yellow! (Front)", 1000, 30, 430 );
                --DOWN
                elseif dir == 1 then
                        text:Textbox( name, "Nothin' wrong with yellow! (Back)", 1000, 30, 430 );
                --LEFT
                elseif dir == 2 then
                        text:Textbox( name, "Nothin' wrong with yellow! (Right)", 1000, 30, 430 );
                --RIGHT
                elseif dir == 3 then
                        text:Textbox( name, "Nothin' wrong with yellow! (Left)", 1000, 30, 430 );
                end
        elseif obj == 04 then
                --UP
                if dir == 0 then
                        text:Textbox( name, "Umm, is that an orange?? (Front)", 1000, 30, 430 );
                --DOWN
                elseif dir == 1 then
                        text:Textbox( name, "Umm, is that an orange?? (Back)", 1000, 30, 430 );
                --LEFT
                elseif dir == 2 then
                        text:Textbox( name, "Umm, is that an orange?? (Right)", 1000, 30, 430 );
                --RIGHT
                elseif dir == 3 then
                        text:Textbox( name, "Umm, is that an orange?? (Left)", 1000, 30, 430 );
                end
        elseif obj == 05 then
                --UP
                if dir == 0 then
                        text:Textbox( name, "The sign reads: 'Home of Biggy Gowey'", 1000, 30, 430 );
                --DOWN
                elseif dir == 1 then

                --LEFT
                elseif dir == 2 then

                --RIGHT
                elseif dir == 3 then
                        text:Textbox( name, "If only I were standing in FRONT of the freakin' sign.", 1000, 30, 430 );
                end
	elseif obj == 06 then
                --UP
                if dir == 0 then
                        text:Textbox( name, "Caution:  Wet Paint.", 1000, 30, 430 );
                --DOWN
                elseif dir == 1 then
                        
                --LEFT
                elseif dir == 2 then
                        
                --RIGHT
                elseif dir == 3 then
                        
                end
	elseif obj == 09 then
                --UP
                if dir == 0 then
                        text:Textbox( name, "Ben is so bad ass.", 1000, 30, 430 );
                --DOWN
                elseif dir == 1 then
                        
                --LEFT
                elseif dir == 2 then
                        
                --RIGHT
                elseif dir == 3 then
                        
                end
        else
                text:Textbox( name, "You see nothing of importance here.", 1000, 30, 430 );
        end
end