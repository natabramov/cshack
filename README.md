This is a hack for Counter-Strike : Global Offensive, where this activates the console variable, 'r_drawothermodels', through overwriting in-memory instruction bytes in the CS:GO process memory.

This project was completed through practicing with bots, and is updated for the latest patch. The explanation for this project is below.


Pictured: Generic Player Models in Spawn Area
![image](https://github.com/natabramov/cshack/assets/108837521/f3dedc5a-daf7-4864-8941-1a4deb3fbba9)

After running the program, the player model wireframes are shown through walls are give the player wall hacks.
![image](https://github.com/natabramov/cshack/assets/108837521/4aac59b9-fdc2-4442-afb1-c902229d37c6)
![image](https://github.com/natabramov/cshack/assets/108837521/01c062f7-6875-4a61-8f29-f37e67cc664f)

Explanation: 

Valve Corporation, CS:GO's developers, released an open source SDK for their software: https://github.com/ValveSoftware/source-sdk-2013
I used this SDK to find where the console variable, 'r_drawothermodels', is manipulated in their client-side software: https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/game/client/c_baseanimating.cpp#L3050

Through an open source debugger for Windows (https://github.com/x64dbg/x64dbg) I was able to connect the CS:GO process to the debugger and analyze the x86 assembly code within the client.dll.

I found the conditional statements in the Valve SDK that correspond to the activation of this console variable. Each 'cmp' instruction is consistent with the 'if' statements in the SDK's client file.
![image](https://github.com/natabramov/cshack/assets/108837521/3445fc5f-80d8-4f48-a1f6-79e141673694)

Before the highlighted instruction, there is a comparison of the register 'edx' to 2, which is in alignment with this 'if' statement found in Valve's SDK:

![image](https://github.com/natabramov/cshack/assets/108837521/71cdd623-9e99-4c34-9e69-1ec0b33a61bb)

The highlighted instruction then moves 20 to register 'ecx' if the comparison of 'edx' and 2 is true. 20 is the hex value for the blue wire frame model. This can be found in Valve's SDK here: 

![image](https://github.com/natabramov/cshack/assets/108837521/26a6526e-1f58-46c2-a049-2ff89fab6a2f)

Finally, my program will overwrite the highlighted value so that this instruction will always hold true, and will always move 20 into register 'ecx'. I achieved this by comparing 'ecx' to 'ecx' which will always hold true.







