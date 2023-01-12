from PIL import Image, ImageFilter

before = Image.open("images/tower.bmp")
after = before.filter(ImageFilter.BoxBlur(10))
after.save("out.bmp")