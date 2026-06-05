import { ref } from 'vue';

export default {
    setup() {
        const count = ref(0);
        const html = '<h1 style="color:green">Hello World!</h1>';
        const dynamicId = "someId";
        function increment() {
            count.value++;
        }
        function addContent() {
            document.getElementById(dynamicId).innerText = 'Hello';
        };
        function displayTime() {
            document.getElementById("time").innerText = Date.now().toLocaleString();
        }
        return {
            count,
            html,
            dynamicId,
            addContent,
            displayTime,
            increment
        }
    }
    // },
    // template:/* HTML */ `<div>
    //                         <span style="color:red">
    //                             Count is {{count}}
    //                         </span>
    //                         <br>
    //                     </div>
    //                     `
}
