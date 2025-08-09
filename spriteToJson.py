from PIL import Image
import json
import os

def spritesheet_to_json_with_tags_empty_tag(png_path, frame_width, frame_height, frame_names, output_json):
    sheet = Image.open(png_path)
    sheet_width, sheet_height = sheet.size

    frames = []
    frame_index = 0

    cols = sheet_width // frame_width
    rows = sheet_height // frame_height

    max_frames = cols * rows
    if len(frame_names) != max_frames:
        raise ValueError(f"frame_names 개수({len(frame_names)})가 스프라이트 시트 총 프레임 수({max_frames})와 다릅니다.")

    for row in range(rows):
        for col in range(cols):
            x = col * frame_width
            y = row * frame_height
            frame_box = (x, y, x + frame_width, y + frame_height)
            frame_img = sheet.crop(frame_box)

            frame_name = frame_names[frame_index]

            frames.append({
                "filename": frame_name,
                "frame": {
                    "x": x,
                    "y": y,
                    "w": frame_width,
                    "h": frame_height
                },

                "duration" : 100
            })

            frame_index += 1

    json_data = {
        "frames": frames, 
        "meta": {
            "app": "CustomSpriteSheetTool",
            "version": "1.0",
            "image": os.path.basename(png_path),
            "size": {"w": sheet_width, "h": sheet_height},
            "frameTags": [],   # 비워둠, 수동으로 태그 작성 가능
            "scale": "1"
        }
    }

    with open(output_json, "w", encoding="utf-8") as f:
        json.dump(json_data, f, ensure_ascii=False, indent=4)

    print(f"JSON saved to {output_json}")

# 사용 예시
img = Image.open("Sour_Run_Spine-animation.png")
sheet_width, sheet_height = img.size

frame_width = 440
frame_height = 400

sheet_col = sheet_width // frame_width
sheet_row = sheet_height // frame_height
sheet_total = sheet_col * sheet_row

frame_names = [f"frame_{i}" for i in range(sheet_total)]

spritesheet_to_json_with_tags_empty_tag(
    png_path="Sour_Run_Spine-animation.png",
    frame_width=440,
    frame_height=400,
    frame_names=frame_names,
    output_json="sprites_with_empty_tags.json"
)
