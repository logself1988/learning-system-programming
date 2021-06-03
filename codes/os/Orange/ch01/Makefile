
TARGET = boot
IMAGE = a.img

$(TARGET): $(TARGET).asm 
	nasm $@.asm -o $@.bin
	dd if=$@.bin of=$(IMAGE) bs=512 count=1 conv=notrunc

clean:
	rm -f $(TARGET).bin $(IMAGE)