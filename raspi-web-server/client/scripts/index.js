const socket = io();

let owieNumber = 0;

socket.on('owie-increment', (data) => {
  owieNumber += 1;
  $('.owie-counter').text(owieNumber);
  if (owieNumber > 1)
    $('.owie-plural').text('s');
});
