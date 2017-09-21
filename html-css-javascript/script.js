
var isScrolling = false;
window.addEventListener('scroll', function() {
	if (document.documentElement.scrollTop > (window.innerHeight - document.getElementById('head').getBoundingClientRect().height - 1)) {
           		
           		initBrackets();
           	}
        if(document.documentElement.scrollTop > (window.innerHeight + document.getElementById('head').getBoundingClientRect().height - 1)){
           	
           	document.getElementById('goals1').classList.remove('goalsstill');
           	if (document.documentElement.scrollTop > (2*(window.innerHeight - document.getElementById('head').getBoundingClientRect().height) - 1)){
    		
           		document.getElementById('about').classList.remove('goalsstill');
        	} else {
        		
           		document.getElementById('about').classList.add('goalsstill');
        	}
           	
        }
        
        else {
			document.getElementById('goals1').classList.add('goalsstill');
			
           	document.getElementById('about').classList.add('goalsstill');
			
			
        }    
	
	
});
function scrollToSmooth(element, to, duration) {
    var start = element.scrollTop,
        change = to - start,
        currentTime = 0,
        increment = 20;
        
    var animateScroll = function(){        
        currentTime += increment;
        var val = Math.easeInOutQuad(currentTime, start, change, duration);
        element.scrollTop = val;
        if(currentTime < duration) {
            setTimeout(animateScroll, increment);
            
        }
        else {
        	isScrolling=false;
        }
    };
    animateScroll();
}

//t = current time
//b = start value
//c = change in value
//d = duration
Math.easeInOutQuad = function (t, b, c, d) {
  t /= d/2;
	if (t < 1) return c/2*t*t + b;
	t--;
	return -c/2 * (t*(t-2) - 1) + b;
};


function workPage() {
	var scrollHeight = 0;
	if (!isScrolling){
	isScrolling=true;
	window.scrollToSmooth(document.documentElement, scrollHeight, 1000);}
}

function goalsPage() {
	var scrollHeight = window.innerHeight - document.getElementById('head').getBoundingClientRect().height;
	if (!isScrolling){
	isScrolling=true;
	window.scrollToSmooth(document.documentElement, scrollHeight, 1000);}
}

function aboutPage() {
	var scrollHeight = 2*(window.innerHeight - document.getElementById('head').getBoundingClientRect().height);
	if (!isScrolling){
		
		isScrolling=true;
		window.scrollToSmooth(document.documentElement, scrollHeight, 1000);
	}
}


function initBrackets(){
	document.getElementById('curlbracketlimg').classList.add('bracketlfade');
	document.getElementById('curlbracketrimg').classList.add('bracketrfade');
}

