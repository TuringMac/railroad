window.onload = init;

function init(){
	const year = document.getElementById("year");
	year.addEventListener('input', checkAge);
	
	function checkAge() {
	if(year.value >= new Date().getFullYear()-18)
		showParent(1);
	else
		showParent(0);
}

function showParent(flag) {
  let parent = document.getElementById("parent");
  if(flag)
	parent.style.display='';
  else
	parent.style.display='none';
}
}

