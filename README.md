# folder-machine-code implementation
part 1(initial part)
首先，我們會對溫溼度感測器、button、RGB、LCD進行初始化的動作。

part 2
接著，在switch的前面，每進到一次loop()中，我們都會去記得現在的buttonState，並且在switch的後面，也會把這次的buttonState給beforeState，以方便之後判斷button是在甚麼時候被按下。

part 3
而在case 0的時候，這時候會去偵測button是否有被按下，如果被按下的話，就會開始去偵測光敏電阻的值，而我在測試的時候發現當有衣服遮在上面的話，光敏電阻的值一定會小於300，因此在之後每一次只要值小於300的話，就代表上面是有擺衣服的，而當上面是有擺衣服的話，就讓它進到state 1，並且在LCD上顯示”Start sampling”，而如果沒有的話，RGB就會亮紅燈，並且在LCD上顯示”No Clothes”，並且留在state 0，等待下一次button 被按下去的時候。

part 4(state 1 : measuring)
而一進到state 1的時候，會每隔四秒量一次它的溼度，總共量三次，並且顯示在LCD上，而為甚麼要隔四秒量三次的原因是因為如果只量第一次的話，怕會被上一次偵測的值影響，像是上一件偵測的是一件溼的衣服。

part 5(state : decide to whether fold the cloth or not)
而假設在最後一次量的溼度是小於一定的值的話(濕度可能要視當天的情況而定)，則代表這件衣服已經乾了，這時候機器就可以準備開始進行折衣服的動作，並且亮起RGB的藍燈和把state設成2，而假設是大於一定的值的話，就代表這件衣服還有一點溼，現在就把它折起來不太適合，因此這時候會亮起RGB的紅燈，並且在LCD上顯示”Too we so back to state 0”。

part 6(state 2)
而在state 2時，就會開始進行伺服馬達折衣服的動作，並且在三個伺服馬達都完成後，在LCD上顯示”Finish folding”。

