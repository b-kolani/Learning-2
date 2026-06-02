function fn() {
    const element = document.createElement('p');
    element.className = "func-result";
    element.textContent = "This script was sent by the backend!";
    document.body.append(element);
}

fn();